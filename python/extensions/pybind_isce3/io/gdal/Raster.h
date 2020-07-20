#pragma once

#include <pybind11/pybind11.h>

#include <isce3/io/gdal/Raster.h>

namespace py = pybind11;

void addbinding(py::class_<isce::io::gdal::Raster> &);

py::buffer_info toBuffer(isce::io::gdal::Raster &);

isce::io::gdal::Raster toRaster(py::buffer);
