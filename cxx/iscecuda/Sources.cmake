set(SOURCES
core/Event.cu
core/gpuBicubicInterpolator.cu
core/gpuBilinearInterpolator.cu
core/gpuLUT1d.cu
core/gpuLUT2d.cu
core/gpuPoly2d.cu
core/gpuProjections.cu
core/gpuSinc2dInterpolator.cu
core/gpuSpline2dInterpolator.cu
core/Orbit.cu
core/Stream.cu
except/Error.cpp
fft/detail/CufftWrapper.cu
geometry/Geo2rdr.cpp
geometry/gpuDEMInterpolator.cu
geometry/gpuGeo2rdr.cu
geometry/gpuGeometry.cu
geometry/gpuRTC.cu
geometry/gpuTopo.cu
geometry/gpuTopoLayers.cpp
geometry/Topo.cpp
geometry/utilities.cu
image/gpuResampSlc.cu
image/ResampSlc.cpp
matchtemplate/ampcor/c2r.cu
matchtemplate/ampcor/correlate.cu
matchtemplate/ampcor/detect.cu
matchtemplate/ampcor/maxcor.cu
matchtemplate/ampcor/migrate.cu
matchtemplate/ampcor/nudge.cu
matchtemplate/ampcor/offsets.cu
matchtemplate/ampcor/r2c.cu
matchtemplate/ampcor/refStats.cu
matchtemplate/ampcor/sat.cu
matchtemplate/ampcor/tgtStats.cu
signal/gpuAzimuthFilter.cu
signal/gpuCrossMul.cu
signal/gpuFilter.cu
signal/gpuLooks.cu
signal/gpuRangeFilter.cu
signal/gpuSignal.cu
)
