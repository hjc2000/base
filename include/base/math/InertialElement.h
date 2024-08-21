#pragma once
#include <stdint.h>

namespace base
{
    /// @brief 一阶惯性环节。
    class InertialElement final
    {
    private:
        double _inertial_time_constant = 0;
        double _sample_interval = 0.001;
        double _kx = 1;
        double _ky = 1;
        double _current_output = 0;

    public:
        /// @brief 一阶惯性环节。
        /// @param inertial_time_constant 惯性时间常数。
        /// @param sample_interval 采样周期。
        InertialElement(double inertial_time_constant, double sample_interval)
        {
            _inertial_time_constant = inertial_time_constant;
            _sample_interval = sample_interval;

            _kx = _sample_interval / (inertial_time_constant + _sample_interval);
            _ky = inertial_time_constant / (inertial_time_constant + _sample_interval);
        }

        /// @brief 向惯性环节输入一个值，并获取该值产生的输出。
        /// @param x
        /// @return
        double Input(double x)
        {
            _current_output = _ky * _current_output + _kx * x;
            return _current_output;
        }
    };
} // namespace base
