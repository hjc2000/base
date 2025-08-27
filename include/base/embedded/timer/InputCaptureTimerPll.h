#pragma once
#include "base/Console.h"
#include "base/embedded/timer/InputCaptureTimer.h"
#include "base/math/Int64Fraction.h"
#include <cstdint>
#include <string>
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

	public:
		InputCaptureTimerPll(base::input_capture_timer::InputCaptureTimer &timer,
							 base::Int64Fraction const &kp,
							 CounterType adjust_limit,
							 CounterType expected_capture_value)
			: _timer(timer),
			  _kp(kp),
			  _origin_period(timer.CounterPeriod()),
			  _adjust_limit(adjust_limit),
			  _expected_capture_value(expected_capture_value)
		{
		}

		void Adjust(CounterType capture_value)
		{
			try
			{
				int64_t error = static_cast<std::make_signed_t<CounterType>>(_expected_capture_value - capture_value);
				int64_t delta = static_cast<int64_t>(_kp * error);

				if (delta > static_cast<int64_t>(_adjust_limit))
				{
					delta = static_cast<int64_t>(_adjust_limit);
				}
				else if (delta < -static_cast<int64_t>(_adjust_limit))
				{
					delta = -static_cast<int64_t>(_adjust_limit);
				}

				int64_t period = static_cast<int64_t>(_origin_period) - delta;
				if (period < 1)
				{
					period = 1;
				}

				_timer.SetCounterPeriodPreloadValue(period);
				base::console.Write("delta = ");
				base::console.Write(std::to_string(delta));
				base::console.WriteLine();
			}
			catch (...)
			{
			}
		}
	};

} // namespace base
