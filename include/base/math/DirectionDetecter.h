#pragma once
#include <iostream>
#include <stdexcept>

namespace base
{
	///
	/// @brief 上升阈值
	///
	/// @note 本次输入值比锚点增加多少就认为当前方向是上升。
	///
	class DirectionDetecter_RisingThreshold
	{
	private:
		double _value = 0;

	public:
		///
		/// @brief 上升阈值
		/// @param value
		///
		explicit DirectionDetecter_RisingThreshold(double value)
		{
			if (value <= 0)
			{
				throw std::invalid_argument{"不允许 <= 0"};
			}

			_value = value;
		}

		double Value() const
		{
			return _value;
		}
	};

	///
	/// @brief 下降阈值
	///
	/// @note 本次输入值比锚点减少多少就认为当前方向是下降。
	///
	class DirectionDetecter_FallenThreshold
	{
	private:
		double _value = 0;

	public:
		///
		/// @brief 下降阈值
		///
		/// @param value
		///
		explicit DirectionDetecter_FallenThreshold(double value)
		{
			if (value >= 0)
			{
				throw std::invalid_argument{"不允许 >= 0"};
			}

			_value = value;
		}

		double Value() const
		{
			return _value;
		}
	};

	///
	/// @brief 初始锚点
	///
	class DirectionDetecter_InitialAnchor
	{
	private:
		double _value = 0;

	public:
		///
		/// @brief 初始锚点
		///
		/// @param value
		///
		explicit DirectionDetecter_InitialAnchor(double value)
		{
			_value = value;
		}

		double Value() const
		{
			return _value;
		}
	};

	///
	/// @brief 当前方向
	///
	enum class DirectionDetecter_Direction
	{
		Rising,
		Falling,
	};

	///
	/// @brief 方向的变化
	///
	enum class DirectionDetecter_DirectionChange
	{
		///
		/// @brief 方向没有变化
		///
		None,

		///
		/// @brief 从上升方向变成了下降方向
		///
		FromRisingToFalling,

		///
		/// @brief 从下降方向变成了上升方向
		///
		FromFallingToRising,
	};

	///
	/// @brief 方向检测器。
	///
	class DirectionDetecter
	{
	private:
		double _rising_threshold = 1;
		double _fallen_threshold = 1;

		double _current_position = 0;
		double _anchor_point = 0;

		DirectionDetecter_Direction _current_direction = DirectionDetecter_Direction::Falling;
		DirectionDetecter_Direction _last_direction = DirectionDetecter_Direction::Falling;

		///
		/// @brief 方向切换瞬间的输入值
		///
		double _turning_point = 0;

		DirectionDetecter_DirectionChange _direction_change = DirectionDetecter_DirectionChange::None;

		///
		/// @brief 更新 _direction_change 字段。
		///
		void UpdateDirectionChangeField()
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

	public:
		///
		/// @brief 构造方向检测器
		///
		/// @param rising_threshold 上升阈值。当前输入值比锚点值大多少才会认为当前方向是上升。
		/// @param fallen_threshold 下降阈值。当前输入值比锚点值小多少才会认为当前方向是下降。
		/// @param initial_direction 初始方向。
		/// @param initial_anchor 初始锚点。
		///
		DirectionDetecter(base::DirectionDetecter_RisingThreshold const &rising_threshold,
						  base::DirectionDetecter_FallenThreshold const &fallen_threshold,
						  DirectionDetecter_Direction initial_direction,
						  DirectionDetecter_InitialAnchor const &initial_anchor)
		{
			_rising_threshold = rising_threshold.Value();
			_fallen_threshold = fallen_threshold.Value();
			_last_direction = initial_direction;
			_current_direction = initial_direction;
			_anchor_point = initial_anchor.Value();
			_current_position = initial_anchor.Value();
		}

		///
		/// @brief 输入一个值，会与历史比较以检测方向的变化。
		///
		/// @param value
		///
		void Input(double value)
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

			// 将当前输入与锚点比较
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

		///
		/// @brief 当前位置。
		///
		/// @note 没调用过 Input 则是初始位置。调用过 Input 则是最近一次调用 Input 时传入的值。
		///
		/// @return
		///
		double CurrentPosition() const
		{
			return _current_position;
		}

		///
		/// @brief 锚点位置。
		/// @return
		///
		double AnchorPoint() const
		{
			return _anchor_point;
		}

		///
		/// @brief 最近一次转折点。即最近一次方向切换的点。
		///
		/// @return
		///
		double TurningPoint() const
		{
			return _turning_point;
		}

		DirectionDetecter_Direction CurrentDirection() const
		{
			return _current_direction;
		}

		DirectionDetecter_Direction LastDirection() const
		{
			return _last_direction;
		}

		///
		/// @brief 检查最近一次输入后方向的变化情况。
		///
		/// @return
		///
		DirectionDetecter_DirectionChange DirectionChange() const
		{
			return _direction_change;
		}
	};

	inline void TestDirectionDetecter()
	{
		base::DirectionDetecter detecter{
			base::DirectionDetecter_RisingThreshold{20},
			base::DirectionDetecter_FallenThreshold{-10},
			base::DirectionDetecter_Direction::Falling,
			base::DirectionDetecter_InitialAnchor{0},
		};

		for (int i = 0; i < 40; i++)
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

		for (int i = 40; i > 0; i--)
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

} // namespace base
