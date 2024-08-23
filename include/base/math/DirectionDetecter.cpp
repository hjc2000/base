#include "DirectionDetecter.h"

using namespace base;

void base::DirectionDetecter::UpdateDirectionChangeField()
{
    if (_last_direction == DirectionDetecter_Direction::Falling &&
        _current_direction == DirectionDetecter_Direction::Rising)
    {
        _direction_change = DirectionDetecter_DirectionChange::FromFallingToRising;
        return;
    }

    if (_last_direction == DirectionDetecter_Direction::Rising &&
        _current_direction == DirectionDetecter_Direction::Falling)
    {
        _direction_change = DirectionDetecter_DirectionChange::FromRisingToFalling;
        return;
    }

    _direction_change = DirectionDetecter_DirectionChange::None;
}

base::DirectionDetecter::DirectionDetecter(base::DirectionDetecter_RisingThreshold const &rising_threshold,
                                           base::DirectionDetecter_FallenThreshold const &fallen_threshold,
                                           DirectionDetecter_Direction initial_direction,
                                           int64_t initial_value)
{
    _rising_threshold = rising_threshold.Value();
    _fallen_threshold = fallen_threshold.Value();
    _last_direction = initial_direction;
    _current_direction = initial_direction;
    _anchor_point = initial_value;
    _current_position = initial_value;
}

void base::DirectionDetecter::Input(int64_t value)
{
    _current_position = value;

    // 将当前输入与锚点比较
    if (_current_position - _anchor_point >= _rising_threshold)
    {
        // 移动量超过阈值，不是干扰
        // 当前是上升方向
        _current_direction = DirectionDetecter_Direction::Rising;
        if (_last_direction != _current_direction)
        {
            // 上次相对锚点移动的的方向与这次相对锚点移动的方向不同，发生了方向变化。
            // 记录转折点
            _turning_point = _anchor_point;
            UpdateDirectionChangeField();
        }

        // 移动量超过阈值，不是干扰，将锚点移动到当前位置
        _anchor_point = _current_position;
        _last_direction = _current_direction;
        return;
    }

    if (_current_position - _anchor_point <= _fallen_threshold)
    {
        // 移动量超过阈值，不是干扰
        // 当前是下降方向
        _current_direction = DirectionDetecter_Direction::Falling;
        if (_last_direction != _current_direction)
        {
            // 上次相对锚点移动的的方向与这次相对锚点移动的方向不同，发生了方向变化。
            // 记录转折点
            _turning_point = _anchor_point;
            UpdateDirectionChangeField();
        }

        // 移动量超过阈值，不是干扰，将锚点移动到当前位置
        _anchor_point = _current_position;
        _last_direction = _current_direction;
        return;
    }

    _direction_change = base::DirectionDetecter_DirectionChange::None;
}

#if HAS_THREAD
void base::Test_DirectionDetecter()
{
    base::DirectionDetecter detecter{
        base::DirectionDetecter_RisingThreshold{20},
        base::DirectionDetecter_FallenThreshold{-10},
        base::DirectionDetecter_Direction::Falling,
        0,
    };

    for (int i = 0; i < 30; i++)
    {
        detecter.Input(i);
        if (detecter.DirectionChange() == base::DirectionDetecter_DirectionChange::FromFallingToRising)
        {
            std::cout << "从下降变成上升。转折点" << detecter.TurningPoint() << std::endl;
        }
        else if (detecter.DirectionChange() == base::DirectionDetecter_DirectionChange::FromRisingToFalling)
        {
            std::cout << "从上升变成下降。转折点" << detecter.TurningPoint() << std::endl;
        }
    }

    for (int i = 30; i > 0; i--)
    {
        detecter.Input(i);
        if (detecter.DirectionChange() == base::DirectionDetecter_DirectionChange::FromFallingToRising)
        {
            std::cout << "从下降变成上升。转折点" << detecter.TurningPoint() << std::endl;
        }
        else if (detecter.DirectionChange() == base::DirectionDetecter_DirectionChange::FromRisingToFalling)
        {
            std::cout << "从上升变成下降。转折点" << detecter.TurningPoint() << std::endl;
        }
    }
}
#endif
