#pragma once
#include "base/embedded/timer/InputCaptureTimer.h"
#include "base/math/Int64Fraction.h"
#include "base/math/math.h"
#include <cstdint>

namespace base
{
	class InputCaptureTimerPll
	{
	private:
		base::input_capture_timer::InputCaptureTimer &_timer;
		base::Int64Fraction _kp{1, 10};
		uint32_t _adjust_limit = 10;
		uint32_t _expected_capture_value = 0;

	public:
		InputCaptureTimerPll(base::input_capture_timer::InputCaptureTimer &timer,
							 base::Int64Fraction const &kp,
							 uint32_t adjust_limit,
							 uint32_t expected_capture_value)
			: _timer(timer),
			  _kp(kp),
			  _adjust_limit(base::abs(adjust_limit)),
			  _expected_capture_value(expected_capture_value)
		{
		}

		void Adjust(uint32_t capture_value)
		{
			int64_t error = static_cast<int64_t>(_expected_capture_value) - static_cast<int64_t>(capture_value);
			int64_t delta = static_cast<int64_t>(_kp * error);

			if (delta > _adjust_limit)
			{
				delta = _adjust_limit;
			}
			else if (delta < -_adjust_limit)
			{
				delta = -_adjust_limit;
			}

			_timer.SetCounterPeriodPreloadValue(_timer.CounterPeriod() + delta);
		}
	};

} // namespace base
