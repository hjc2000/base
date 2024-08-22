#pragma once
#include <stdint.h>

namespace base
{
    class InertialElement_TimeConstant
    {
    private:
        double _value = 0;

    public:
        explicit InertialElement_TimeConstant(double value)
        {
            _value = value;
        }

        double Value() const
        {
            return _value;
        }
    };

    class InertialElement_SampleInterval
    {
    private:
        double _value = 0;

    public:
        explicit InertialElement_SampleInterval(double value)
        {
            _value = value;
        }

        double Value() const
        {
            return _value;
        }
    };

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
        InertialElement(InertialElement_TimeConstant const &inertial_time_constant,
                        InertialElement_SampleInterval const &sample_interval);

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
