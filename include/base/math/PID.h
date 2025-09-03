#pragma once
#include "base/math/Fraction.h"
#include "base/math/Int64Fraction.h"
#include "base/math/math.h"
#include "base/string/define.h"
#include <stdexcept>

namespace base
{
	template <typename T>
	class PID
	{
	private:
		T _current_output{};
		T _kp{};
		T _ki{};
		T _kd{};
		T _x[3]{};
		T _resolution{};
		T _max_output{};
		T _min_output{};

		constexpr void LimitOutput()
		{
			if (_current_output < _min_output)
			{
				_current_output = _min_output;
			}
			else if (_current_output > _max_output)
			{
				_current_output = _max_output;
			}
		}

	public:
		///
		/// @brief 无参构造。构造的 PID 处于不可用状态。
		/// 设置这个构造函数是为了支持延迟初始化。
		///
		constexpr PID() = default;

		///
		/// @brief 构造 PID 控制器。
		///
		/// @param kp 比例系数。
		/// @param ki 积分系数。
		/// @param kd 微分系数。
		/// @param resolution 输出分辨率。
		/// @param max_output 允许的最大输出。
		/// @param min_output 允许的最小输出。
		///
		constexpr PID(T kp,
					  T ki,
					  T kd,
					  T resolution,
					  T max_output,
					  T min_output)
		{
			if (max_output < min_output)
			{
				// 允许 max_output == min_output, 因为有些时候需要将输出钳制在某一个值上。
				throw std::invalid_argument{CODE_POS_STR + "max_output 不能 < min_output."};
			}

			_kp = kp;
			_ki = ki;
			_kd = kd;
			_resolution = resolution;
			_max_output = max_output;
			_min_output = min_output;
		}

		///
		/// @brief 向 PID 控制器输入一个数，迭代计算后更新输出。
		///
		/// @param x
		/// @return
		///
		constexpr T Input(T x)
		{
			_x[2] = _x[1];
			_x[1] = _x[0];
			_x[0] = x;

			_current_output += _kp * (_x[0] - _x[1]);
			_current_output += _ki * _x[0];
			_current_output += _kd * (_x[0] - 2 * _x[1] + _x[2]);

			_current_output = base::reduce_resolution(_current_output, _resolution);
			LimitOutput();
			return _current_output;
		}

		///
		/// @brief PID 控制器当前输出。
		///
		/// @return
		///
		constexpr T CurrentOutput() const
		{
			return _current_output;
		}

		///
		/// @brief 比例系数。
		///
		/// @return
		///
		constexpr T Kp() const
		{
			return _kp;
		}

		///
		/// @brief 积分系数。
		///
		/// @return
		///
		constexpr T Ki() const
		{
			return _ki;
		}

		///
		/// @brief 微分系数。
		///
		/// @return
		///
		constexpr T Kd() const
		{
			return _kd;
		}

		///
		/// @brief 允许的最大输出。
		///
		/// @return
		///
		constexpr T MaxOutput() const
		{
			return _max_output;
		}

		///
		/// @brief 设置允许的最大输出。
		///
		/// @note 下一次输入数据进行迭代时生效。
		/// @note 本方法不会立刻对当前输出进行限制。
		///
		/// @param value
		///
		constexpr void SetMaxOutput(T const &value)
		{
			_max_output = value;
		}

		///
		/// @brief 允许的最小输出。
		///
		/// @return
		///
		constexpr T MinOutput() const
		{
			return _min_output;
		}

		///
		/// @brief 设置允许的最小输出。
		///
		/// @note 下一次输入数据进行迭代时生效。
		/// @note 本方法不会立刻对当前输出进行限制。
		///
		/// @param value
		///
		constexpr void SetMinOutput(T const &value)
		{
			_min_output = value;
		}

		///
		/// @brief 设置输出限制。
		///
		/// @note 下一次输入数据进行迭代时生效。
		/// @note 本方法不会立刻对当前输出进行限制。
		///
		/// @param max_output
		/// @param min_output
		///
		constexpr void SetOutputLimit(T const &max_output, T const &min_output)
		{
			_max_output = max_output;
			_min_output = min_output;
		}
	};

} // namespace base
