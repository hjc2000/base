#pragma once
#include <cstdlib>

namespace base
{
	///
	/// @brief 线性插值器
	///
	///
	template <typename T>
	class LinearInterpolator final
	{
	private:
		T _current_value = 0;
		T _end_value = 0;
		T _step_length = 0;

	public:
		LinearInterpolator() = default;

		LinearInterpolator(T current_value, T end_value, T step_length)
		{
			_current_value = current_value;
			_end_value = end_value;
			_step_length = std::abs(step_length);
		}

		///
		/// @brief 当前值。
		///
		/// @return
		///
		T CurrentValue() const
		{
			return _current_value;
		}

		///
		/// @brief 设置当前值。
		///
		/// @param value
		///
		void SetCurrentValue(T value)
		{
			_current_value = value;
		}

		///
		/// @brief 结束值。
		///
		/// @return
		///
		T EndValue() const
		{
			return _end_value;
		}

		///
		/// @brief 设置结束值。
		///
		/// @param value
		///
		void SetEndValue(T value)
		{
			_end_value = value;
		}

		///
		/// @brief 步长。
		///
		/// @return
		///
		T StepLength() const
		{
			return _step_length;
		}

		///
		/// @brief 设置步长。
		///
		/// @param value
		///
		void SetStepLength(T value)
		{
			_step_length = value;
		}

		///
		/// @brief 按照步长迈出一步，让当前值逼近结束值。
		///
		/// @return 迈出一步后的当前值。
		///
		T Step()
		{
			if (std::abs(_end_value - _current_value) < _step_length)
			{
				// 差距小于 1 个步长，直接赋值为结束值。
				_current_value = _end_value;
				return _current_value;
			}

			// 差距大于 1 个步长。
			// 从正向和负向逼近结束值。
			if (_current_value < _end_value)
			{
				_current_value += _step_length;
			}
			else if (_current_value > _end_value)
			{
				_current_value -= _step_length;
			}
		}
	};
} // namespace base
