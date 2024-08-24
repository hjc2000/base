#pragma once
#include <base/math/Fraction.h>

namespace base
{
    /// @brief 信号源接口。
    /// @tparam SignalType 信号值的类型。
    template <typename SignalType>
    class ISignalSource
    {
    public:
        /// @brief 采样间隔。单位：秒。
        /// @return
        virtual base::Fraction SampleInterval() const = 0;

        /// @brief 设置采样间隔。单位：秒。
        /// @param value
        virtual void SetSampleInterval(base::Fraction value) = 0;

        /// @brief 打开采样器。
        virtual void Open() = 0;

        /// @brief 采样一次。
        /// @note 此调用会阻塞，直到时间距离上一次采样过去了 SampleInterval
        /// @return 采样值。
        virtual SignalType Sample() = 0;
    };
} // namespace base
