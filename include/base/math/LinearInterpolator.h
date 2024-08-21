#pragma once
#include <stdint.h>

namespace base
{
    /// @brief 线性插值器的步数。
    class LinearInterpolator_StepCount
    {
    private:
        int _value = 0;

    public:
        LinearInterpolator_StepCount(int value)
        {
            _value = value;
        }

        int Value() const
        {
            return _value;
        }
    };

    /// @brief 线性插值器
    class LinearInterpolator final
    {
    private:
        double _start_value = 0;
        double _end_value = 0;
        double _step_length = 0;
        double _current_value = 0;

    public:
        LinearInterpolator(double start_value, double end_value, double step_length);

        LinearInterpolator(double start_value, double end_value, LinearInterpolator_StepCount step_count);

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

        double CurrentValue() const
        {
            return _current_value;
        }

        /// @brief 前缀递增
        /// @return
        double operator++();

        /// @brief 后缀递增
        /// @param
        /// @return
        double operator++(int);
    };
} // namespace base
