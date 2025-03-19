#include "HysteresisElement.h"

base::HysteresisElement::HysteresisElement(HysteresisElement_RisingThreshold const &rising_threshold,
										   HysteresisElement_FallenThreshold const &fallen_threshold)
{
	_rising_threshold = rising_threshold.Value();
	_fallen_threshold = fallen_threshold.Value();
}

void base::HysteresisElement::ChangeThreshold(HysteresisElement_RisingThreshold const &rising_threshold,
											  HysteresisElement_FallenThreshold const &fallen_threshold)
{
	_rising_threshold = rising_threshold.Value();
	_fallen_threshold = fallen_threshold.Value();
	Input(_x);
}

bool base::HysteresisElement::Input(double x)
{
	_x = x;
	_last_output = _current_output;
	if (x >= _rising_threshold)
	{
		_current_output = true;
	}
	else if (x <= _fallen_threshold)
	{
		_current_output = false;
	}

	return _current_output;
}

base::HysteresisElement_OutputChange base::HysteresisElement::OutputChange() const
{
	if (!_last_output && _current_output)
	{
		return HysteresisElement_OutputChange::Rise;
	}

	if (_last_output && !_current_output)
	{
		return HysteresisElement_OutputChange::Fall;
	}

	return HysteresisElement_OutputChange::None;
}
