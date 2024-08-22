#pragma once
#include <stdint.h>

namespace base
{
#pragma region 参数类

    /// @brief 惯性时间常数
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

    /// @brief 采样周期
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

#pragma endregion

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
        double Input(double x);

        /// @brief 当前的输出。
        /// @return
        double CurrentOutput() const;

        /// @brief 更改惯性时间常数
        /// @param inertial_time_constant
        void ChangeParameter(InertialElement_TimeConstant const &inertial_time_constant);

        /// @brief 更改采样周期
        /// @param sample_interval
        void ChangeParameter(InertialElement_SampleInterval const &sample_interval);

        /// @brief 更改惯性时间常数和采样周期。
        /// @param inertial_time_constant
        /// @param sample_interval
        void ChangeParameter(InertialElement_TimeConstant const &inertial_time_constant,
                             InertialElement_SampleInterval const &sample_interval);
    };
} // namespace base
