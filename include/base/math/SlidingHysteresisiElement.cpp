#include "SlidingHysteresisiElement.h"

base::SlidingHysteresisiElement::SlidingHysteresisiElement(HysteresisElement_RisingThreshold const &rising_threshold,
														   HysteresisElement_FallenThreshold const &fallen_threshold)
	: _hys(rising_threshold, fallen_threshold)
{
}

bool base::SlidingHysteresisiElement::Input(double x)
{
	double last_input = _hys.CurrentInput();
	bool ret = _hys.Input(x);

	if (x - last_input > 0)
	{
		// 当前是上升方向
		if (x > _hys.RisingThreshold())
		{
			_hys.MoveX(x - _hys.RisingThreshold());
		}
	}
	else
	{
		// 当前是下降方向
		if (x < _hys.FallenThreshold())
		{
			_hys.MoveX(x - _hys.FallenThreshold());
		}
	}

	return ret;
}
