#pragma once
#include <stdint.h>

namespace base
{
    class LinearInterpolator final
    {
    private:
        double _start_value = 0;
        double _end_value = 0;
        double _step_length = 0;
        double _current_value = 0;

    public:
        LinearInterpolator(double start_value, double end_value, double step_length);
        LinearInterpolator(double start_value, double end_value, int step_count);

        double StartValue() const
        {
            return _start_value;
        }

        double EndValue() const
        {
            return _end_value;
        }

        void SetEndValue(double value)
        {
            _end_value = value;
        }

        double StepLength() const
        {
            return _step_length;
        }

        bool IsCompleted();

        /// @brief 前缀递增
        /// @return
        double operator++();

        /// @brief 后缀递增
        /// @param
        /// @return
        double operator++(int);
    };
} // namespace base
