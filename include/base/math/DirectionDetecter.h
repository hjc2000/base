#pragma once

#ifndef HAS_THREAD
#define HAS_THREAD 0
#endif

#include <stdexcept>
#include <stdint.h>

namespace base
{
#pragma region 参数类

    /// @brief 上升阈值
    /// @note 本次输入值比锚点增加多少就认为当前方向是上升。
    class DirectionDetecter_RisingThreshold
    {
    private:
        int64_t _value = 0;

    public:
        /// @brief 上升阈值
        /// @param value
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
    /// @note 本次输入值比锚点减少多少就认为当前方向是下降。
    class DirectionDetecter_FallenThreshold
    {
    private:
        int64_t _value = 0;

    public:
        /// @brief 下降阈值
        /// @param value
        explicit DirectionDetecter_FallenThreshold(int64_t value)
        {
            if (value >= 0)
            {
                throw std::invalid_argument{"不允许 >= 0"};
            }

            _value = value;
        }

        int64_t Value() const
        {
            return _value;
        }
    };

#pragma endregion

#pragma region 枚举
    /// @brief 当前方向
    enum class DirectionDetecter_Direction
    {
        Rising,
        Falling,
    };

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
#pragma endregion

    /// @brief 方向检测器。
    class DirectionDetecter
    {
    private:
        int64_t _rising_threshold = 1;
        int64_t _fallen_threshold = 1;

        int64_t _current_position = 0;
        int64_t _anchor_point = 0;

        DirectionDetecter_Direction _current_direction = DirectionDetecter_Direction::Falling;
        DirectionDetecter_Direction _last_direction = DirectionDetecter_Direction::Falling;

        /// @brief 方向切换瞬间的输入值
        int64_t _turning_point = 0;
        DirectionDetecter_DirectionChange _direction_change = DirectionDetecter_DirectionChange::None;

        /// @brief 更新 _direction_change 字段。
        void UpdateDirectionChangeField();

    public:
        /// @brief 构造方向检测器
        /// @param rising_threshold 上升阈值。当前输入值比锚点值大多少才会认为当前方向是上升。
        /// @param fallen_threshold 下降阈值。当前输入值比锚点值小多少才会认为当前方向是下降。
        /// @param initial_direction 初始方向。
        /// @param initial_anchor 初始锚点。
        DirectionDetecter(base::DirectionDetecter_RisingThreshold const &rising_threshold,
                          base::DirectionDetecter_FallenThreshold const &fallen_threshold,
                          DirectionDetecter_Direction initial_direction,
                          int64_t initial_anchor);

        /// @brief 输入一个值，会与历史比较以检测方向的变化。
        /// @param value
        void Input(int64_t value);

        /// @brief 当前位置。
        /// @note 没调用过 Input 则是初始位置。调用过 Input 则是最近一次调用 Input 时传入的值。
        /// @return
        int64_t CurrentPosition() const
        {
            return _current_position;
        }

        /// @brief 锚点位置。
        /// @return
        int64_t AnchorPoint() const
        {
            return _anchor_point;
        }

        /// @brief 最近一次转折点。即最近一次方向切换的点。
        /// @return
        int64_t TurningPoint() const
        {
            return _turning_point;
        }

        /// @brief 检查最近一次输入后方向的变化情况。
        /// @return
        DirectionDetecter_DirectionChange DirectionChange() const
        {
            return _direction_change;
        }
    };

#if HAS_THREAD
    void Test_DirectionDetecter();
#endif

} // namespace base
