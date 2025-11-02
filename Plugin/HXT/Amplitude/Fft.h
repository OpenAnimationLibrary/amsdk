#if !defined FFT_H
#define FFT_H
#include "StdAfx.h"
#include "Macros.h"
#include <complex>
#include <vector>

typedef std::complex<double> Complex;

class Fft {
public:
    Fft(unsigned points, unsigned sampleRate);
    // Hard work
    void Transform(std::vector<int> const &data);
    // Output: from i = 0 to points-1
    [[nodiscard]] double GetIntensity(const unsigned i) const {
        ASSERT(i < _points);
        return std::abs(_X[i]) / _sqrtPoints;
    }

    [[nodiscard]] unsigned Points() const {
        return _points;
    }

    [[nodiscard]] int Points_asInt() const {
        return (int)_points;
    }

    // return frequency in Hz of a given point
    [[nodiscard]] int GetFrequency(const unsigned point) const {
        ASSERT(point < _points);
        const long x = _sampleRate * point;
        return x / _points;
    }

    [[nodiscard]] int HzToNearestPoint(const int freq) const {
        if (freq > (int)_sampleRate)
            return _points - 1;
        const double temp = _points * freq / (double)_sampleRate;
        return RoundValue(temp);
    }

    [[nodiscard]] int HzToPoint(const int freq) const {
        return (long)_points * freq / _sampleRate;
    }

    [[nodiscard]] int MaxFreq() const {
        return _sampleRate;
    }

private:
    void DataIn(std::vector<int> const &data);

    void PutAt(const unsigned i, const double val) {
        _X[_aBitRev[i]] = Complex(val);
    }

private:
    unsigned _points;
    unsigned _sampleRate;
    unsigned _logPoints;		// binary log of _points
    double _sqrtPoints;	// square root of _points

    std::vector<unsigned> _aBitRev{};	// bit reverse vector
    std::vector<Complex> _X{};	// in-place fft array
    std::vector<std::vector<Complex>> _W{};	// exponentials
    std::vector<double> _tape{};	// recording tape
};

#endif
