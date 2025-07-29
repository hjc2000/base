#include "SinSignalSource.h"
#include "base/string/define.h"
#include <math.h>
#include <stdexcept>

base::SinSignalSource::SinSignalSource(base::unit::Second sin_periodic)
	: _sample_clock(sin_periodic)
{
}

base::unit::Second base::SinSignalSource::SampleInterval() const
{
	return _sample_interval;
}

void base::SinSignalSource::Open(base::unit::Second const &sample_interval)
{
	_opened = true;
	_sample_interval = sample_interval;
}

double base::SinSignalSource::Sample()
{
	if (!_opened)
	{
		throw std::runtime_error{CODE_POS_STR + "打开后才能采样。"};
	}

	// y = sin(w * t)
	// w = 2pi / T
	// y = sin(2pi / T * t)
	double sample_value = sin(2 * M_PI *
							  static_cast<double>(_sample_clock.CurrentTime()) /
							  static_cast<double>(_sample_clock.Period()));

	_sample_clock += _sample_interval;
	return sample_value;
}
