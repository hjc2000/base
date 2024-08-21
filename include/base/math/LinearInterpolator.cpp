#include "LinearInterpolator.h"

base::LinearInterpolator::LinearInterpolator(double start_value, double end_value, double step_length)
{
    _start_value = start_value;
    _end_value = end_value;
    _step_length = step_length;
    _current_value = start_value;
}

base::LinearInterpolator::LinearInterpolator(double start_value, double end_value, LinearInterpolator_StepCount step_count)
{
    _start_value = start_value;
    _end_value = end_value;
    _step_length = (end_value - start_value) / step_count.Value();
    _current_value = start_value;
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
