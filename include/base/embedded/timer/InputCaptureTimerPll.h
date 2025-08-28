#pragma once
#include "base/Console.h"
#include "base/embedded/timer/InputCaptureTimer.h"
#include "base/math/Int64Fraction.h"
#include "base/math/PID.h"
#include "base/string/define.h"
#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <string>

namespace base
{
	class InputCaptureTimerPll
	{
	private:
		base::input_capture_timer::InputCaptureTimer &_timer;
		int64_t _multiple = 1;
		int64_t _adjust_limit{};
		int64_t _expected_capture_value{};

		int64_t _additional_capture_period = 0;

		int64_t _last_capture_value{};
		int64_t _current_capture_value{};
		int64_t _captured_signal_period{};

		///
		/// @brief 锁频环 PID.
		///
		///
		base::PID<base::Int64Fraction> _fll_pid{};

		base::PID<base::Int64Fraction> _pll_pid{};

		bool _adjust_started = false;

	public:
		InputCaptureTimerPll(base::input_capture_timer::InputCaptureTimer &timer,
							 int64_t multiple,
							 int64_t adjust_limit,
							 int64_t expected_capture_value)
			: _timer(timer)
		{
			if (multiple <= 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "非法 multiple."};
			}

			_multiple = multiple;
			_adjust_limit = adjust_limit;
			_expected_capture_value = expected_capture_value;
			_current_capture_value = expected_capture_value;

			_fll_pid = base::PID<base::Int64Fraction>{
				base::Int64Fraction{1, 100},
				base::Int64Fraction{1, 1000},
				0,
				base::Int64Fraction{1, INT16_MAX},
				static_cast<int64_t>(adjust_limit),
				-static_cast<int64_t>(adjust_limit),
			};

			_pll_pid = base::PID<base::Int64Fraction>{
				base::Int64Fraction{1, 100},
				base::Int64Fraction{1, 1000},
				0,
				base::Int64Fraction{1, INT16_MAX},
				static_cast<int64_t>(adjust_limit),
				-static_cast<int64_t>(adjust_limit),
			};

			base::console.WriteLine(std::string{"multiple = "} + std::to_string(multiple));
		}

		void UpdateCaptureValue(int64_t capture_value)
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

			// PI 控制锁频
			int64_t fll_error = _captured_signal_period - _timer.CounterPeriod() * _multiple;

			{
				base::Int64Fraction pid_output = _fll_pid.Input(fll_error);
				int64_t int_pid_output{pid_output};
				int_pid_output /= _multiple;
				_timer.SetCounterPeriodPreloadValue(_timer.CounterPeriod() + int_pid_output);
			}

			int64_t const pll_output_limit = std::min<int64_t>(static_cast<int64_t>(_adjust_limit),
															   static_cast<int64_t>(_timer.CounterPeriod() / 4));

			if (fll_error > pll_output_limit)
			{
				// 锁频环误差过大，锁相环不工作，直接返回。
				return;
			}
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
