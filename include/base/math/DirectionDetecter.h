#pragma once
#include <stdexcept>
#include <stdint.h>

namespace base
{
    /// @brief 上升阈值
    /// @note 本次输入值比上次增加多少就认为当前方向是上升。
    class DirectionDetecter_RisingThreshold
    {
    private:
        int64_t _value = 0;

    public:
        explicit DirectionDetecter_RisingThreshold(int64_t value)
        {
            if (value <= 0)
            {
                throw std::invalid_argument{"不允许 <= 0"};
            }

            _value = value;
        }

        int64_t Value() const
        {
            return _value;
        }
    };

    /// @brief 下降阈值
    /// @note 本次输入值比上次减少多少就认为当前方向是下降。
    class DirectionDetecter_FallenThreshold
    {
    private:
        int64_t _value = 0;

    public:
        explicit DirectionDetecter_FallenThreshold(int64_t value)
        {
            if (value <= 0)
            {
                throw std::invalid_argument{"不允许 <= 0"};
            }

            _value = value;
        }

        int64_t Value() const
        {
            return _value;
        }
    };

    /// @brief 方向检测器。
    class DirectionDetecter
    {
    private:
        int64_t _rising_threshold = 1;
        int64_t _fallen_threshold = 1;
        int64_t _last_input = 0;

        /// @brief 方向切换瞬间的输入值
        int64_t _input_value_at_direction_changing = 0;

    public:
        DirectionDetecter(base::DirectionDetecter_RisingThreshold const &rising_threshold,
                          base::DirectionDetecter_FallenThreshold const &fallen_threshold)
        {
            _rising_threshold = rising_threshold.Value();
            _fallen_threshold = fallen_threshold.Value();
        }
    };
} // namespace base
