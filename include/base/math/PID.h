#pragma once
#include "base/math/FastInt64Fraction.h"
#include "base/string/define.h"
#include <stdexcept>

namespace base
{
	class PID
	{
	private:
		base::FastInt64Fraction _current_output{};
		base::FastInt64Fraction _kp{};
		base::FastInt64Fraction _ki{};
		base::FastInt64Fraction _kd{};
		base::FastInt64Fraction _x[3]{};
		base::FastInt64Fraction _max_output{};
		base::FastInt64Fraction _min_output{};

		void LimitOutput()
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
		PID() = default;

		///
		/// @brief 构造 PID 控制器。
		///
		/// @param kp 比例系数。
		/// @param ki 积分系数。
		/// @param kd 微分系数。
		/// @param max_output 允许的最大输出。
		/// @param min_output 允许的最小输出。
		///
		PID(base::FastInt64Fraction kp,
			base::FastInt64Fraction ki,
			base::FastInt64Fraction kd,
			base::FastInt64Fraction max_output,
			base::FastInt64Fraction min_output)
		{
			if (max_output < min_output)
			{
				// 允许 max_output == min_output, 因为有些时候需要将输出钳制在某一个值上。
				throw std::invalid_argument{CODE_POS_STR + "max_output 不能 < min_output."};
			}

			_kp = kp;
			_ki = ki;
			_kd = kd;
			_max_output = max_output;
			_min_output = min_output;
		}

		///
		/// @brief 向 PID 控制器输入一个数，迭代计算后更新输出。
		///
		/// @param x
		/// @return
		///
		base::FastInt64Fraction Input(base::FastInt64Fraction x)
		{
			_x[2] = _x[1];
			_x[1] = _x[0];
			_x[0] = x;

			_current_output += _kp * (_x[0] - _x[1]);
			_current_output += _ki * _x[0];
			_current_output += _kd * (_x[0] - 2 * _x[1] + _x[2]);

			LimitOutput();
			return _current_output;
		}

		///
		/// @brief PID 控制器当前输出。
		///
		/// @return
		///
		base::FastInt64Fraction CurrentOutput() const
		{
			return _current_output;
		}

		///
		/// @brief 比例系数。
		///
		/// @return
		///
		base::FastInt64Fraction Kp() const
		{
			return _kp;
		}

		///
		/// @brief 积分系数。
		///
		/// @return
		///
		base::FastInt64Fraction Ki() const
		{
			return _ki;
		}

		///
		/// @brief 微分系数。
		///
		/// @return
		///
		base::FastInt64Fraction Kd() const
		{
			return _kd;
		}

		///
		/// @brief 允许的最大输出。
		///
		/// @return
		///
		base::FastInt64Fraction MaxOutput() const
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
		void SetMaxOutput(base::FastInt64Fraction const &value)
		{
			_max_output = value;
		}

		///
		/// @brief 允许的最小输出。
		///
		/// @return
		///
		base::FastInt64Fraction MinOutput() const
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
		void SetMinOutput(base::FastInt64Fraction const &value)
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
		void SetOutputLimit(base::FastInt64Fraction const &max_output, base::FastInt64Fraction const &min_output)
		{
			_max_output = max_output;
			_min_output = min_output;
		}
	};

} // namespace base
