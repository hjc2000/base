#pragma once
#include "base/embedded/timer/InputCaptureTimer.h"
#include "base/math/Int64Fraction.h"
#include "base/math/math.h"
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
		base::Int64Fraction _kp{1, 10};
		CounterType _origin_period{};
		CounterType _adjust_limit{};
		CounterType _expected_capture_value{};
		bool _current_capture_value_changed = false;
		CounterType _current_capture_value{};
		CounterType _current_capture_value_interpolation{};

	public:
		InputCaptureTimerPll(base::input_capture_timer::InputCaptureTimer &timer,
							 base::Int64Fraction const &kp,
							 CounterType adjust_limit,
							 CounterType expected_capture_value)
			: _timer(timer)
		{
			_kp = kp;
			_origin_period = timer.CounterPeriod();
			_adjust_limit = adjust_limit;
			_expected_capture_value = expected_capture_value;
			_current_capture_value = expected_capture_value;
			_current_capture_value_interpolation = expected_capture_value;
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

				int64_t delta = static_cast<int64_t>(_kp * error);

				if (error != 0 && delta == 0)
				{
					// 误差过小，乘上 kp 后截断了，但是误差确实存在，需要调整。
					if (base::abs(error) > 1)
					{
						delta = error / 2;
					}
					else
					{
						delta = error / error;
					}
				}

				if (delta > static_cast<int64_t>(_adjust_limit))
				{
					delta = static_cast<int64_t>(_adjust_limit);
				}
				else if (delta < -static_cast<int64_t>(_adjust_limit))
				{
					delta = -static_cast<int64_t>(_adjust_limit);
				}

				int64_t period = static_cast<int64_t>(_origin_period) + delta;
				if (period < 1)
				{
					period = 1;
				}

				_timer.SetCounterPeriodPreloadValue(period);

				// 因为定时时间到中断触发的频率比捕获中断触发的频率高，所以在下次捕获前需要对
				// 捕获值进行插值。
				_current_capture_value_interpolation -= delta;
			}
			catch (...)
			{
			}
		}
	};

} // namespace base
