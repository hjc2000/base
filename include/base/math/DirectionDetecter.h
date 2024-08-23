#pragma once
#include <stdexcept>
#include <stdint.h>

namespace base
{
#pragma region 参数类

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

#pragma endregion

    /// @brief 方向的变化
    enum class DirectionDetecter_DirectionChange
    {
        /// @brief 方向没有变化
        None,

        /// @brief 从上升方向变成了下降方向
        FromRisingToFalling,

        /// @brief 从下降方向变成了上升方向
        FromFallingToRising,
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

        DirectionDetecter_DirectionChange Input(int64_t value)
        {
            if (value - _last_input > _rising_threshold)
            {
                // 当前是上升方向
            }
        }
    };
} // namespace base
