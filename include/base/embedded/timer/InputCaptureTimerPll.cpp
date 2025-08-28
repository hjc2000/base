#include "InputCaptureTimerPll.h" // IWYU pragma: keep
#include "base/Console.h"
#include "base/string/define.h"
#include <cstdint>
#include <stdexcept>
#include <string>

void base::InputCaptureTimerPll::LockFrequency()
{
	_fll_error = _captured_signal_period - _timer.CounterPeriod() * _multiple;

	_fll_pid.SetOutputLimit(static_cast<int64_t>(_timer.CounterPeriod() / 2),
							-static_cast<int64_t>(_timer.CounterPeriod() / 2));

	base::Int64Fraction pid_output = _fll_pid.Input(_fll_error);
	int64_t int_pid_output{pid_output};
	int_pid_output /= _multiple;
	_timer.SetCounterPeriodPreloadValue(_timer.CounterPeriod() + int_pid_output);
}

void base::InputCaptureTimerPll::LockPhase()
{
	int64_t const pll_output_limit = _timer.CounterPeriod() / 10;

	if (_fll_error > pll_output_limit)
	{
		// 锁频环误差过大，锁相环不工作，直接返回。
		return;
	}

	_pll_error = _current_capture_register_value - _expected_capture_value;

	// 把相位误差分给距离下次捕获会经历的 _multiple 个周期去调整。
	_pll_ajustment = _pll_error / _multiple;
	if (_pll_ajustment == 0 && _pll_error != 0)
	{
		_pll_fine_error = _pll_error;
		return;
	}

	if (_pll_ajustment < -pll_output_limit)
	{
		_pll_ajustment = -pll_output_limit;
	}
	else if (_pll_ajustment > pll_output_limit)
	{
		_pll_ajustment = pll_output_limit;
	}

	_timer.SetCounterPeriodPreloadValue(_timer.CounterPeriod() + _pll_ajustment);
}

base::InputCaptureTimerPll::InputCaptureTimerPll(base::input_capture_timer::InputCaptureTimer &timer,
												 int64_t multiple,
												 int64_t expected_capture_value)
	: _timer(timer)
{
	if (multiple <= 0)
	{
		throw std::invalid_argument{CODE_POS_STR + "非法 multiple."};
	}

	_multiple = multiple;
	_expected_capture_value = expected_capture_value;
	_current_capture_value = expected_capture_value;

	_fll_pid = base::PID<base::Int64Fraction>{
		base::Int64Fraction{1, 100},
		base::Int64Fraction{1, 1000},
		0,
		base::Int64Fraction{1, INT16_MAX},
		static_cast<int64_t>(_timer.CounterPeriod() / 2),
		-static_cast<int64_t>(_timer.CounterPeriod() / 2),
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

	_pll_fine_error = 0;

	_timer.SetCounterPeriodPreloadValue(_timer.CounterPeriod() - _pll_ajustment);
	_pll_ajustment = 0;

	_timer.SetCounterPeriodPreloadValue(_timer.CounterPeriod() - _pll_fine_ajustment);
	_pll_fine_ajustment = 0;

	LockFrequency();
	LockPhase();
}

void base::InputCaptureTimerPll::OnPeriodElapsed()
{
	_additional_capture_period += _timer.CounterPeriod();

	if (!_adjust_started)
	{
		// 第一次进来，不进行调整工作
		return;
	}

	if (_pll_fine_error > 0)
	{
		_pll_fine_error--;
		if (_pll_fine_ajustment == 0)
		{
			_timer.SetCounterPeriodPreloadValue(_timer.CounterPeriod() + 1);
			_pll_fine_ajustment = 1;
		}
	}
	else if (_pll_fine_error < 0)
	{
		_pll_fine_error++;
		if (_pll_fine_ajustment == 0)
		{
			_timer.SetCounterPeriodPreloadValue(_timer.CounterPeriod() - 1);
			_pll_fine_ajustment = -1;
		}
	}

	if (_pll_fine_error == 0)
	{
		_timer.SetCounterPeriodPreloadValue(_timer.CounterPeriod() - _pll_fine_ajustment);
		_pll_fine_ajustment = 0;
	}
}
