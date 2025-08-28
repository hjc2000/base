#pragma once
#include "base/Console.h"
#include "base/embedded/timer/InputCaptureTimer.h"
#include "base/math/Int64Fraction.h"
#include "base/math/math.h"
#include "base/math/PID.h"
#include "base/string/define.h"
#include <cstdint>
#include <stdexcept>
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
		int64_t _multiple = 1;
		CounterType _origin_period{};
		CounterType _adjust_limit{};
		CounterType _expected_capture_value{};

		int64_t _additional_capture_period = 0;

		int64_t _last_capture_value{};
		int64_t _current_capture_value{};
		int64_t _captured_signal_period{};

		base::PID<base::Int64Fraction> _pid{};
		bool _adjust_started = false;

	public:
		InputCaptureTimerPll(base::input_capture_timer::InputCaptureTimer &timer,
							 int64_t multiple,
							 CounterType adjust_limit,
							 CounterType expected_capture_value)
			: _timer(timer)
		{
			if (multiple <= 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "非法倍数。"};
			}

			_multiple = multiple;
			_adjust_limit = adjust_limit;
			_expected_capture_value = expected_capture_value;
			_current_capture_value = expected_capture_value;

			_pid = base::PID<base::Int64Fraction>{
				base::Int64Fraction{1, 100},
				base::Int64Fraction{0, 1},
				0,
				base::Int64Fraction{1, INT16_MAX},
				static_cast<int64_t>(adjust_limit),
				-static_cast<int64_t>(adjust_limit),
			};

			base::console.WriteLine(std::string{"multiple = "} + std::to_string(multiple));
		}

		void UpdateCaptureValue(CounterType capture_value)
		{
			_last_capture_value = _current_capture_value;
			_current_capture_value = capture_value + _additional_capture_period;
			_captured_signal_period = _current_capture_value - _last_capture_value + _additional_capture_period;
			_additional_capture_period = 0;

			if (!_adjust_started)
			{
				// 第一次进来，不进行调整工作
				_adjust_started = true;
				return;
			}

			int64_t error = _captured_signal_period - _timer.CounterPeriod() * _multiple;
			base::Int64Fraction pid_output = _pid.Input(error);
			int64_t int_pid_output{pid_output};
			int_pid_output /= _multiple;
			_timer.SetCounterPeriodPreloadValue(_timer.CounterPeriod() + int_pid_output);
		}

		void OnPeriodElapsed()
		{
			_additional_capture_period += _timer.CounterPeriod();
		}

		///
		/// @brief 当前捕获值。
		///
		/// @note 已经处理了定时周期小于被捕获信号周期导致的溢出问题。本属性读取的捕获值
		/// 就是无溢出的理论情况下的捕获值。
		///
		/// @return
		///
		int64_t CurrentCaptureValue() const
		{
			return _current_capture_value;
		}

		///
		/// @brief 被捕获的信号的周期。
		///
		/// @return
		///
		int64_t CapturedSignalPeriod() const
		{
			return _captured_signal_period;
		}
	};

} // namespace base
