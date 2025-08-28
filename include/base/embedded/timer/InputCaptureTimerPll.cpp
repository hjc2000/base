#include "InputCaptureTimerPll.h" // IWYU pragma: keep
#include "base/Console.h"
#include "base/string/define.h"
#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <string>

base::InputCaptureTimerPll::InputCaptureTimerPll(base::input_capture_timer::InputCaptureTimer &timer,
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

	base::console.WriteLine(std::string{"multiple = "} + std::to_string(multiple));
}

void base::InputCaptureTimerPll::UpdateCaptureValue(int64_t capture_value)
{
	_current_capture_register_value = capture_value;
	_last_capture_value = _current_capture_value;
	_current_capture_value = _current_capture_register_value + _additional_capture_period;
	_captured_signal_period = _current_capture_value - _last_capture_value + _additional_capture_period;
	_additional_capture_period = 0;

	if (!_adjust_started)
	{
		// 第一次进来，不进行调整工作
		_adjust_started = true;
		return;
	}

	// PI 控制锁频
	{
		_fll_error = _captured_signal_period - _timer.CounterPeriod() * _multiple;
		base::Int64Fraction pid_output = _fll_pid.Input(_fll_error);
		int64_t int_pid_output{pid_output};
		int_pid_output /= _multiple;
		_timer.SetCounterPeriodPreloadValue(_timer.CounterPeriod() + int_pid_output);
	}
}

void base::InputCaptureTimerPll::OnPeriodElapsed()
{
	_additional_capture_period += _timer.CounterPeriod();

	if (!_adjust_started)
	{
		return;
	}

	int64_t const pll_output_limit = std::min<int64_t>(static_cast<int64_t>(_adjust_limit - _fll_pid.CurrentOutput().Abs()),
													   static_cast<int64_t>(_timer.CounterPeriod() / 4));

	if (_fll_error > pll_output_limit)
	{
		// 锁频环误差过大，锁相环不工作，直接返回。
		return;
	}
}
