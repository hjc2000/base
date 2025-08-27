#pragma once

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

	public:
		constexpr PID(T kp, T ki, T kd)
		{
		}

		constexpr T Input(T x)
		{
			_x[2] = _x[1];
			_x[1] = _x[0];
			_x[0] = x;

			_current_output += _kp * (_x[0] - _x[1]);
			_current_output += _ki * _x[0];
			_current_output += _kd * (_x[0] - 2 * _x[1] + _x[2]);
			return _current_output;
		}
	};

} // namespace base
