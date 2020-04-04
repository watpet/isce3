#pragma once

#include <isce/core/Kernels.h>
#include <pybind11/pybind11.h>

// "Trampoline" class allowing inheritance in Python
template <typename T>
class PyKernel : public isce::core::Kernel<T> {
public:
    // Can't figure out why this isn't working :(
    // T operator()(double x) const override {
    //     PYBIND11_OVERLOAD_PURE_NAME(T, isce::core::Kernel<T>, operator(), "__call__", x);
    // }
};

template <typename T>
void addbinding(pybind11::class_<isce::core::Kernel<T>, PyKernel<T>> &);

template <typename T>
void addbinding(pybind11::class_<isce::core::BartlettKernel<T>, isce::core::Kernel<T>> &);

template <typename T>
void addbinding(pybind11::class_<isce::core::LinearKernel<T>, isce::core::Kernel<T>> &);

template <typename T>
void addbinding(pybind11::class_<isce::core::KnabKernel<T>, isce::core::Kernel<T>> &);

template <typename T>
void addbinding(pybind11::class_<isce::core::NFFTKernel<T>, isce::core::Kernel<T>> &);

template <typename T>
void addbinding(pybind11::class_<isce::core::TabulatedKernel<T>, isce::core::Kernel<T>> &);

template <typename T>
void addbinding(pybind11::class_<isce::core::ChebyKernel<T>, isce::core::Kernel<T>> &);
