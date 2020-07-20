#cython: language_level=3

cdef extern from "isce3/core/Pixel.h" namespace "isce::core":
    cdef cppclass Pixel:
        Pixel() except +
        Pixel(double, double, size_t) except +
