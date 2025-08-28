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
		constexpr PID() = default;

		constexpr PID(T kp,
					  T ki,
					  T kd,
					  T resolution,
					  T max_output,
					  T min_output)
		{
			if (max_output <= min_output)
			{
				throw std::invalid_argument{CODE_POS_STR + "max_output 不能 <= min_output."};
			}

			_kp = kp;
			_ki = ki;
			_kd = kd;
			_resolution = resolution;
			_max_output = max_output;
			_min_output = min_output;
		}

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

		constexpr T CurrentOutput() const
		{
			return _current_output;
		}

		constexpr T Kp() const
		{
			return _kp;
		}

		constexpr T Ki() const
		{
			return _ki;
		}

		constexpr T Kd() const
		{
			return _kd;
		}

		constexpr T MaxOutput() const
		{
			return _max_output;
		}

		constexpr void SetMaxOutput(T const &value)
		{
			_max_output = value;
			LimitOutput();
		}

		constexpr T MinOutput() const
		{
			return _min_output;
		}

		constexpr void SetMinOutput(T const &value)
		{
			_min_output = value;
			LimitOutput();
		}

		constexpr void SetOutputLimit(T const &max_output, T const &min_output)
		{
			_max_output = max_output;
			_min_output = min_output;
			LimitOutput();
		}
	};

} // namespace base
