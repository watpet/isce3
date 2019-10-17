//-*- C++ -*-
//-*- coding: utf-8 -*-

#pragma once

// isce::core
#include <isce/core/Metadata.h>
#include <isce/core/DateTime.h>
#include <isce/core/TimeDelta.h>

// isce::product
#include <isce/product/Product.h>

namespace isce {
    namespace product {
        class RadarGridParameters; 
    }
}

class isce::product::RadarGridParameters {

    public:
        /** Default constructor */
        inline RadarGridParameters() {}

        /** Constructor with a product and number of looks. */
        inline RadarGridParameters(const isce::product::Product & product,
                                   char frequency = 'A',
                                   size_t numberAzimuthLooks = 1,
                                   size_t numberRangeLooks = 1);

        /** Constructor with a swath. */
        inline RadarGridParameters(const isce::product::Swath & swath,
                                   int lookSide,
                                   size_t numberAzimuthLooks = 1,
                                   size_t numberRangeLooks = 1);

        /** Constructor from an isce::core::Metadata object. */
        inline RadarGridParameters(const isce::core::Metadata & meta,
                                   const isce::core::DateTime & refEpoch,
                                   size_t numberAzimuthLooks = 1,
                                   size_t numberRangeLooks = 1);

        /** Constructor from individual components and values. */
        inline RadarGridParameters(size_t numberAzimuthLooks,
                                   size_t numberRangeLooks,
                                   double sensingStart,
                                   double wavelength,
                                   double prf,
                                   double startingRange,
                                   double rangePixelSpacing,
                                   int lookSide,
                                   size_t length,
                                   size_t width,
                                   isce::core::DateTime refEpoch);

        /** Copy constructor */
        inline RadarGridParameters(const RadarGridParameters & rgparam);

        /** Assignment operator */
        inline RadarGridParameters & operator=(const RadarGridParameters & rgparam);

        /** Get the look direction */
        inline int lookSide() const { return _lookSide; }
        /** Set look direction from an integer */
        inline void lookSide(int side) { _lookSide = side; }
        /** Set look direction from a string */
        inline void lookSide(const std::string &);

        /** Get number of azimuth looks */
        inline size_t numberAzimuthLooks() const { return _numberAzimuthLooks; }
        /** Set number of azimuth looks */
        inline void numberAzimuthLooks(const size_t & t) { _numberAzimuthLooks = t; }

        /** Get number of range looks */
        inline size_t numberRangeLooks() const { return _numberRangeLooks; }
        /** Set number of range looks */
        inline void numberRangeLooks(const size_t & t) { _numberRangeLooks = t; }

        /** Get reference epoch */
        inline const isce::core::DateTime & refEpoch() const { return _refEpoch; }

        /** Get sensing start time in seconds */
        inline double sensingStart() const { return _sensingStart; }
        /** Set sensing start time in seconds */
        inline void sensingStart(const double & t) { _sensingStart = t; }

        /** Get radar wavelength */
        inline double wavelength() const { return _wavelength; }
        /** Set radar wavelength */
        inline void wavelength(const double & t) { _wavelength = t; }
        
        /** Get pulse repetition frequency */
        inline double prf() const { return _prf; }
        /** Set pulse repetition frequency */
        inline void prf(const double & t){ _prf = t; }

        /** Get starting slant range */
        inline double startingRange() const { return _startingRange; }
        /** Set starting slant range */
        inline void startingRange(const double & t) { _startingRange = t; }

        /** Get slant range pixel spacing */
        inline double rangePixelSpacing() const { return _rangePixelSpacing; }
        /** Set slant range pixel spacing */
        inline void rangePixelSpacing(const double & t) { _rangePixelSpacing = t; }

        /** Get radar grid length */
        inline size_t length() const { return _rlength; }
        /** Set radar grid length */
        inline void length(const double & t) { _rlength = t; }

        /** Get radar grid width */
        inline size_t width() const { return _rwidth; }
        /** Set radar grid length */
        inline void width(const double & t) { _rwidth = t; }

        /** Get total number of radar grid elements */
        inline size_t size() const { return _rlength * _rwidth; }

        /** Get sensing stop time in seconds */
        inline double sensingStop() const {
            return _sensingStart + (_rlength - 1.0) / _prf;
        }

        /** Get sensing mid time in seconds */
        inline double sensingMid() const {
            return 0.5 * (_sensingStart + sensingStop());
        }

        /** Get sensing time for a given line (row) */
        inline double sensingTime(size_t line) const {
            return _sensingStart + line * _numberAzimuthLooks / _prf;
        }

        /** Get a sensing DateTime for a given line (row) */
        inline isce::core::DateTime sensingDateTime(size_t line) const {
            return _refEpoch + sensingTime(line);
        }

        /** Get ending slant range */
        inline double endingRange() const {
            return _startingRange + (_rwidth - 1.0) * _rangePixelSpacing;
        }

        /** Get middle slant range */
        inline double midRange() const {
            return 0.5 * (_startingRange + endingRange());
        }

        /** Get slant range for a given sample (column) */
        inline double slantRange(size_t sample) const {
            return _startingRange + sample * _numberRangeLooks * _rangePixelSpacing;
        }

    // Protected data members can be accessed by derived classes
    protected:
        size_t _numberAzimuthLooks;
        size_t _numberRangeLooks;
        int _lookSide;
        double _sensingStart;
        double _wavelength;
        double _prf;
        double _startingRange;
        double _rangePixelSpacing;
        size_t _rlength;
        size_t _rwidth;
        isce::core::DateTime _refEpoch;
};

// Constructor with a swath.
/** @param[in] swath Input swath
  * @param[in] numberAzimuthLooks Number of azimuth looks in input geometry
  * @param[in] numberRangeLooks Number of range looks in input geometry */
isce::product::RadarGridParameters::
RadarGridParameters(const isce::product::Swath & swath,
                    int lookSide,
                    size_t numberAzimuthLooks,
                    size_t numberRangeLooks) :
    _numberAzimuthLooks(numberAzimuthLooks),
    _numberRangeLooks(numberRangeLooks),
    _lookSide(lookSide),
    _sensingStart(swath.zeroDopplerTime()[0]),
    _wavelength(swath.processedWavelength()),
    _prf(swath.nominalAcquisitionPRF()),
    _startingRange(swath.slantRange()[0]),
    _rangePixelSpacing(swath.rangePixelSpacing()),
    _rlength(swath.lines()),
    _rwidth(swath.samples()),
    _refEpoch(swath.refEpoch()) {}

// Constructor with a product
/** @param[in] product Input Product
  * @param[in] frequency Frequency designation
  * @param[in] numberAzimuthLooks Number of azimuth looks of input product
  * @param[in] numberRangeLooks Number of range looks of input product */
isce::product::RadarGridParameters::
RadarGridParameters(const isce::product::Product & product,
                    char frequency,
                    size_t numberAzimuthLooks,
                    size_t numberRangeLooks) :
    RadarGridParameters(product.swath(frequency), product.lookSide(), numberAzimuthLooks, numberRangeLooks) {}

// Constructor from an isce::core::Metadata object.
/** @param[in] meta isce::core::Metadata object
  * @param[in] refEpoch Reference epoch date
  * @param[in] numberAzimuthLooks Number of azimuth looks in input geometry
  * @param[in] numberRangeLooks Number of range looks in input geometry */
isce::product::RadarGridParameters::
RadarGridParameters(const isce::core::Metadata & meta,
                    const isce::core::DateTime & refEpoch,
                    size_t numberAzimuthLooks,
                    size_t numberRangeLooks) :
    _numberAzimuthLooks(numberAzimuthLooks),
    _numberRangeLooks(numberRangeLooks),
    _lookSide(meta.lookSide),
    _sensingStart((meta.sensingStart - refEpoch).getTotalSeconds()),
    _wavelength(meta.radarWavelength),
    _prf(meta.prf),
    _startingRange(meta.rangeFirstSample),
    _rangePixelSpacing(meta.slantRangePixelSpacing),
    _rlength(meta.length),
    _rwidth(meta.width),
    _refEpoch(refEpoch) {}

// Copy constructors
/** @param[in] rgparam RadarGridParameters object */
isce::product::RadarGridParameters::
RadarGridParameters(const RadarGridParameters & rgparams) :
    _numberAzimuthLooks(rgparams.numberAzimuthLooks()),
    _numberRangeLooks(rgparams.numberRangeLooks()),
    _lookSide(rgparams.lookSide()),
    _sensingStart(rgparams.sensingStart()),
    _wavelength(rgparams.wavelength()),
    _prf(rgparams.prf()),
    _startingRange(rgparams.startingRange()),
    _rangePixelSpacing(rgparams.rangePixelSpacing()),
    _rlength(rgparams.length()),
    _rwidth(rgparams.width()),
    _refEpoch(rgparams.refEpoch()) {}

// Assignment operator
/** @param[in] rgparam RadarGridParameters object */
isce::product::RadarGridParameters &
isce::product::RadarGridParameters::
operator=(const RadarGridParameters & rgparams) {
    _numberAzimuthLooks = rgparams.numberAzimuthLooks();
    _numberRangeLooks = rgparams.numberRangeLooks();
    _sensingStart = rgparams.sensingStart();
    _wavelength = rgparams.wavelength();
    _prf = rgparams.prf();
    _startingRange = rgparams.startingRange();
    _rangePixelSpacing = rgparams.rangePixelSpacing();
    _lookSide = rgparams.lookSide(),
    _rlength = rgparams.length();
    _rwidth = rgparams.width();
    _refEpoch = rgparams.refEpoch();
    return *this;
}

// Constructor from individual components and values
isce::product::RadarGridParameters::
RadarGridParameters(size_t numberAzimuthLooks,
                    size_t numberRangeLooks,
                    double sensingStart,
                    double wavelength,
                    double prf,
                    double startingRange,
                    double rangePixelSpacing,
                    int lookSide,
                    size_t length,
                    size_t width,
                    isce::core::DateTime refEpoch) :
    _numberAzimuthLooks(numberAzimuthLooks),
    _numberRangeLooks(numberRangeLooks),
    _lookSide(lookSide),
    _sensingStart(sensingStart),
    _wavelength(wavelength),
    _prf(prf),
    _startingRange(startingRange),
    _rangePixelSpacing(rangePixelSpacing),
    _rlength(length),
    _rwidth(width),
    _refEpoch(refEpoch) {}

/** @param[in] look String representation of look side */
void
isce::product::RadarGridParameters::
lookSide(const std::string & inputLook) {
    // Convert to lowercase
    std::string look(inputLook);
    std::for_each(look.begin(), look.end(), [](char & c) {
		c = std::tolower(c);
	});
    // Validate look string before setting
    if (look.compare("right") == 0) {
        _lookSide = -1;
    } else if (look.compare("left") == 0) {
        _lookSide = 1;
    } else {
        pyre::journal::error_t error("isce.product.RadarGridParameters");
        error
            << pyre::journal::at(__HERE__)
            << "Could not successfully set look direction. Not 'right' or 'left'."
            << pyre::journal::endl;
    }
}
