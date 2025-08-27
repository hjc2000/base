#pragma once
#include "base/Console.h"
#include "base/embedded/timer/InputCaptureTimer.h"
#include "base/math/Int64Fraction.h"
#include "base/math/math.h"
#include "base/math/PID.h"
#include <cstdint>
#include <type_traits>

namespace base
{
	template <typename CounterType>
		requires(std::is_unsigned_v<CounterType>)
	class InputCaptureTimerPll
	{
	private:
		base::input_capture_timer::InputCaptureTimer &_timer;
		CounterType _origin_period{};
		CounterType _adjust_limit{};
		CounterType _expected_capture_value{};
		bool _current_capture_value_changed = false;
		CounterType _current_capture_value{};
		CounterType _current_capture_value_interpolation{};
		base::PID<base::Int64Fraction> _pid{};

	public:
		InputCaptureTimerPll(base::input_capture_timer::InputCaptureTimer &timer,
							 CounterType adjust_limit,
							 CounterType expected_capture_value)
			: _timer(timer)
		{
			_origin_period = timer.CounterPeriod();
			_adjust_limit = adjust_limit;
			_expected_capture_value = expected_capture_value;
			_current_capture_value = expected_capture_value;
			_current_capture_value_interpolation = expected_capture_value;

			_pid = base::PID<base::Int64Fraction>{
				base::Int64Fraction{1, 10},
				base::Int64Fraction{1, 5000},
				0,
				base::Int64Fraction{1, INT16_MAX},
				static_cast<int64_t>(adjust_limit),
				-static_cast<int64_t>(adjust_limit),
			};

			base::console.WriteLine(-base::Int64Fraction{static_cast<int64_t>(adjust_limit)});
		}

		void UpdateCaptureValue(CounterType capture_value)
		{
			_current_capture_value = capture_value;
			_current_capture_value_changed = true;
		}

		void Adjust()
		{
			try
			{
				if (_current_capture_value_changed)
				{
					_current_capture_value_changed = false;
					_current_capture_value_interpolation = _current_capture_value;
				}

				int64_t error = static_cast<int64_t>(_current_capture_value_interpolation) - static_cast<int64_t>(_expected_capture_value);
				error %= _origin_period;
				if (error > _origin_period / 2)
				{
					error -= _origin_period;
				}

				base::Int64Fraction output = _pid.Input(error);
				int64_t int_output = static_cast<int64_t>(output);

				int64_t period = static_cast<int64_t>(_origin_period) + int_output;
				if (period < 1)
				{
					period = 1;
				}

				_timer.SetCounterPeriodPreloadValue(period);

				// 因为定时时间到中断触发的频率比捕获中断触发的频率高，所以在下次捕获前需要对
				// 捕获值进行插值。
				int64_t step_p = static_cast<int64_t>(error * _pid.Kp());
				if (base::abs(step_p) < base::abs(int_output))
				{
					_current_capture_value_interpolation -= step_p;
				}
				else
				{
					_current_capture_value_interpolation -= int_output;
				}
			}
			catch (...)
			{
			}
		}
	};

} // namespace base
