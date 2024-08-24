#include "LinearInterpolator.h"

base::LinearInterpolator::LinearInterpolator(LinearInterpolator_StartVlaue const &start_value,
                                             LinearInterpolator_EndVlaue const &end_value,
                                             LinearInterpolator_StepLength const &step_length)
{
    _start_value = start_value.Value();
    _end_value = end_value.Value();
    _step_length = step_length.Value();
    _current_value = _start_value;
}

base::LinearInterpolator::LinearInterpolator(LinearInterpolator_StartVlaue const &start_value,
                                             LinearInterpolator_EndVlaue const &end_value,
                                             LinearInterpolator_StepCount const &step_count)
{
    _start_value = start_value.Value();
    _end_value = end_value.Value();
    _step_length = (_end_value - _start_value) / step_count.Value();
    _current_value = _start_value;
}

bool base::LinearInterpolator::IsCompleted() const
{
    if (_start_value <= _end_value)
    {
        // 步长为正
        return _current_value >= _end_value;
    }

    // 步长为负
    return _current_value <= _end_value;
}

double base::LinearInterpolator::operator++()
{
    if (IsCompleted())
    {
        return _end_value;
    }

    _current_value += _step_length;
    return _current_value;
}

double base::LinearInterpolator::operator++(int)
{
    if (IsCompleted())
    {
        return _end_value;
    }

    double ret = _current_value;
    _current_value += _step_length;
    return ret;
}
