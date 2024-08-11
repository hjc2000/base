#include "SinSignalSource.h"
#include <math.h>
#include <stdexcept>

base::SinSignalSource::SinSignalSource(base::Fraction sin_periodic)
    : _sample_clock(sin_periodic)
{
}

base::Fraction base::SinSignalSource::SampleInterval() const
{
    return _sample_interval;
}

void base::SinSignalSource::SetSampleInterval(base::Fraction value)
{
    if (_opened)
    {
        throw std::runtime_error{"打开后禁止更改属性"};
    }

    _sample_interval = value;
}

void base::SinSignalSource::Open()
{
    _opened = true;
}

double base::SinSignalSource::Sample()
{
    if (!_opened)
    {
        throw std::runtime_error{"打开后才能采样"};
    }

    // y = sin(w * t)
    // w = 2pi / T
    // y = sin(2pi / T * t)
    double sample_value = sin(2 * M_PI *
                              _sample_clock.Time().ToDouble() /
                              _sample_clock.Period().ToDouble());

    _sample_clock += _sample_interval;
    return sample_value;
}
