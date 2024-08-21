#include "HysteresisElement.h"

using namespace base;

bool base::HysteresisElement::Input(double x)
{
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

HysteresisElement_OutputChange base::HysteresisElement::OutputChange()
{
    if (!_last_output && _current_output)
    {
        return HysteresisElement_OutputChange::Rise;
    }
    else if (_last_output && !_current_output)
    {
        return HysteresisElement_OutputChange::Fall;
    }

    return HysteresisElement_OutputChange::None;
}
