// -*- C++ -*-
// -*- coding: utf-8 -*-
//
// Author: Bryan Riel
// Copyright 2017-2018
//

#include "gpuDEMInterpolator.h"

#include <isce/geometry/DEMInterpolator.h>
#include <isce/cuda/core/gpuInterpolator.h>
#include <isce/cuda/except/Error.h>

using isce::core::Vec3;
using isce::cuda::core::ProjectionBase;

/** @param[in] demInterp DEMInterpolator object.
  *
  * Copy DEM interpolator data to GPU device. */
__host__
isce::cuda::geometry::gpuDEMInterpolator::
gpuDEMInterpolator(const isce::geometry::DEMInterpolator & demInterp) :
    _haveRaster(demInterp.haveRaster()), _refHeight(demInterp.refHeight()),
    _length(demInterp.length()), _width(demInterp.width()),
    _xstart(demInterp.xStart()), _ystart(demInterp.yStart()),
    _deltax(demInterp.deltaX()), _deltay(demInterp.deltaY()),
    _epsgcode(demInterp.epsgCode()), _interpMethod(demInterp.interpMethod()),
    _owner(true)
{
    if (_haveRaster) {
        // allocate memory on device for DEM data
        size_t bytes = length() * width() * sizeof(float);
        checkCudaErrors(cudaMalloc(&_dem, bytes));

        // copy DEM data
        checkCudaErrors(
                cudaMemcpy(_dem, demInterp.data(), bytes, cudaMemcpyHostToDevice));
    }
}

/** @param[in] demInterp gpuDEMInterpolator object.
  *
  * Copy DEM interpolator data within GPU device. */
__host__ __device__
isce::cuda::geometry::gpuDEMInterpolator::
gpuDEMInterpolator(isce::cuda::geometry::gpuDEMInterpolator & demInterp) :
    _haveRaster(demInterp.haveRaster()), _refHeight(demInterp.refHeight()),
    _length(demInterp.length()), _width(demInterp.width()),
    _xstart(demInterp.xStart()), _ystart(demInterp.yStart()),
    _deltax(demInterp.deltaX()), _deltay(demInterp.deltaY()),
    _dem(demInterp._dem), _epsgcode(demInterp.epsgCode()),
    _interpMethod(demInterp.interpMethod()), _proj(demInterp.proj()),
    _interp(demInterp.interp()), _owner(false) {}

/** Destructor. */
isce::cuda::geometry::gpuDEMInterpolator::
~gpuDEMInterpolator() {
    // Only owner of memory clears it
    if (_owner and _haveRaster) {
        checkCudaErrors(cudaFree(_dem));
    }
}

/** Kernel for initializing projection and interpolation objects. */
__global__
void initProjInterpKernel(isce::cuda::core::ProjectionBase ** proj,
                          isce::cuda::core::gpuInterpolator<float> ** interp,
                          int epsgCode,
                          isce::core::dataInterpMethod interpMethod) {
    if (threadIdx.x == 0 && blockIdx.x == 0) {
        // Create projection
        (*proj) = isce::cuda::core::createProj(epsgCode);

        // Choose interpolator
        if (interpMethod == isce::core::BILINEAR_METHOD) {
            (*interp) = new isce::cuda::core::gpuBilinearInterpolator<float>();
        } else if (interpMethod == isce::core::BICUBIC_METHOD) {
            (*interp) = new isce::cuda::core::gpuBicubicInterpolator<float>();
        } else if (interpMethod == isce::core::BIQUINTIC_METHOD) {
            (*interp) = new isce::cuda::core::gpuSpline2dInterpolator<float>(6);
        } else {
            (*interp) = new isce::cuda::core::gpuBilinearInterpolator<float>();
        }
    }
}

/** Initialize projection and interpolation objects on device. */
__host__
void isce::cuda::geometry::gpuDEMInterpolator::
initProjInterp() {

    // Allocate projection pointer on device
    checkCudaErrors(cudaMalloc(&_proj, sizeof(isce::cuda::core::ProjectionBase **)));

    // Allocate interpolator pointer on device
    checkCudaErrors(cudaMalloc(&_interp, sizeof(isce::cuda::core::gpuInterpolator<float> **)));

    // Call initialization kernel
    initProjInterpKernel<<<1, 1>>>(_proj, _interp, _epsgcode, _interpMethod);

    // Check for any kernel errors
    checkCudaErrors(cudaPeekAtLastError());
}

/** Kernel for deleting projection and interpolation objects on device. */
__global__
void finalizeProjInterpKernel(isce::cuda::core::ProjectionBase ** proj,
                              isce::cuda::core::gpuInterpolator<float> ** interp) {
    if (threadIdx.x == 0 && blockIdx.x == 0) {
        delete *proj;
        delete *interp;
    }
}

/** Finalize/delete projection and interpolation objects on device. */
__host__
void isce::cuda::geometry::gpuDEMInterpolator::
finalizeProjInterp() {
    // Call finalization kernel
    finalizeProjInterpKernel<<<1, 1>>>(_proj, _interp);

    // Check for any kernel errors
    checkCudaErrors(cudaPeekAtLastError());

    // Free memory for pointers
    checkCudaErrors(cudaFree(_proj));
    checkCudaErrors(cudaFree(_interp));
}

/** @param[out] double* Array of lon-lat-h at middle of DEM. */
__device__
Vec3
isce::cuda::geometry::gpuDEMInterpolator::
midLonLat() const {
    // Create coordinates for middle X/Y
    const Vec3 xyz = {midX(), midY(), _refHeight};
    Vec3 llh;
    // Call projection inverse
    (*_proj)->inverse(xyz, llh);
    return llh;
}

/** @param[in] lon longitude of interpolation point.
  * @param[in] lat latitude of interpolation point.
  * @param[out] value Interpolated DEM height. */
__device__
float
isce::cuda::geometry::gpuDEMInterpolator::
interpolateLonLat(double lon, double lat) const {

    // If we don't have a DEM, just return reference height
    float value = _refHeight;
    if (!_haveRaster) {
        return value;
    }

    // Pass latitude and longitude through projection
    const Vec3 llh { lon, lat, 0. };
    Vec3 xyz;
    (*_proj)->forward(llh, xyz);

    // Interpolate DEM at its native coordinates
    value = interpolateXY(xyz[0], xyz[1]);

    // Done
    return value;
}

/** @param[in] x X-coordinate of interpolation point.
  * @param[in] y Y-coordinate of interpolation point.
  * @param[out] value Interpolated DEM height. */
__device__
float
isce::cuda::geometry::gpuDEMInterpolator::
interpolateXY(double x, double y) const {

    // If we don't have a DEM, just return reference height
    float value = _refHeight;
    if (!_haveRaster) {
        return value;
    }

    // Compute the row and column for requested lat and lon
    const double row = (y - _ystart) / _deltay;
    const double col = (x - _xstart) / _deltax;

    // Check validity of interpolation coordinates
    const int irow = int(std::floor(row));
    const int icol = int(std::floor(col));
    // If outside bounds, return reference height
    if (irow < 2 || irow >= int(_length - 1))
        return _refHeight;
    if (icol < 2 || icol >= int(_width - 1))
        return _refHeight;

    // Delegate DEM interpolation to gpuInterpolator pointer
    value = (*_interp)->interpolate(col, row, _dem, _width, _length);

    // Done
    return value;
}

// end of file