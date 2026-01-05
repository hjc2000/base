#include "InputCaptureTimerPll.h" // IWYU pragma: keep
#include "base/math/FastInt64Fraction.h"
#include "base/math/InertialElement.h"
#include "base/math/math.h"
#include "base/string/define.h"
#include <algorithm>
#include <cstdint>
#include <stdexcept>

void base::InputCaptureTimerPll::LockFrequency()
{
	_captured_signal_period = static_cast<int64_t>(_captured_signal_period_filter.Input(_captured_signal_period));
	_frequency_error = _captured_signal_period - _timer.CounterPeriod() * _frequency_multiple;

	_fll_pid.SetOutputLimit(static_cast<int64_t>(_timer.CounterPeriod() / 2),
							-static_cast<int64_t>(_timer.CounterPeriod() / 2));

	base::FastInt64Fraction pid_output = _fll_pid.Input(_frequency_error);
	int64_t int_pid_output{pid_output};
	int_pid_output /= _frequency_multiple;
	_timer.SetCounterPeriodPreloadValue(_timer.CounterPeriod() + int_pid_output);
}

void base::InputCaptureTimerPll::LockPhase()
{
	int64_t const pll_output_limit = std::min<int64_t>(_timer.CounterPeriod() / 100, 1000);

	if (base::abs(_frequency_error) > pll_output_limit)
	{
		// 锁频环误差过大，锁相环不工作，直接返回。
		return;
	}

	_phase_error = _current_capture_register_value - _expected_capture_value;
	if (_phase_error > static_cast<int64_t>(_timer.CounterPeriod()) / 2)
	{
		_phase_error -= _timer.CounterPeriod();
	}
	else if (_phase_error < -static_cast<int64_t>(_timer.CounterPeriod()) / 2)
	{
		_phase_error += _timer.CounterPeriod();
	}

	// 把相位误差分给距离下次捕获会经历的 _frequency_multiple 个周期去调整。
	_phase_ajustment = _phase_error / _frequency_multiple;
	if (_phase_ajustment < -pll_output_limit)
	{
		_phase_ajustment = -pll_output_limit;
	}
	else if (_phase_ajustment > pll_output_limit)
	{
		_phase_ajustment = pll_output_limit;
	}

	if (_phase_ajustment == 0 && _phase_error != 0)
	{
		_phase_fine_error = _phase_error;
		return;
	}

	_timer.SetCounterPeriodPreloadValue(_timer.CounterPeriod() + _phase_ajustment);
}

base::InputCaptureTimerPll::InputCaptureTimerPll(base::input_capture_timer::InputCaptureTimer &timer,
												 int64_t frequency_multiple,
												 int64_t expected_capture_value)
	: _timer(timer)
{
	if (frequency_multiple <= 0)
	{
		throw std::invalid_argument{CODE_POS_STR + "非法 frequency_multiple."};
	}

	_frequency_multiple = frequency_multiple;
	_expected_capture_value = expected_capture_value;
	_current_capture_value = expected_capture_value;

	_fll_pid = base::PID{
		base::FastInt64Fraction{1, 100},
		base::FastInt64Fraction{1, 1000},
		0,
		static_cast<int64_t>(_timer.CounterPeriod() / 2),
		-static_cast<int64_t>(_timer.CounterPeriod() / 2),
	};

	// 惯性时间常数是采样间隔的 10 倍，单位不重要，反正滤波器要的是这两个的倍数关系。
	base::FastInt64Fraction inertial_time_constant{1};

	_captured_signal_period_filter = base::InertialElement{
		inertial_time_constant,
		inertial_time_constant / 10,
	};

	_captured_signal_period_filter.SetCurrentOutput(_timer.CounterPeriod() * _frequency_multiple);
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

	_phase_fine_error = 0;

	_timer.SetCounterPeriodPreloadValue(_timer.CounterPeriod() - _phase_ajustment);
	_phase_ajustment = 0;

	_timer.SetCounterPeriodPreloadValue(_timer.CounterPeriod() - _phase_fine_ajustment);
	_phase_fine_ajustment = 0;

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

	if (_phase_fine_error > 0)
	{
		_phase_fine_error--;
		if (_phase_fine_ajustment == 0)
		{
			_timer.SetCounterPeriodPreloadValue(_timer.CounterPeriod() + 1);
			_phase_fine_ajustment = 1;
		}
	}
	else if (_phase_fine_error < 0)
	{
		_phase_fine_error++;
		if (_phase_fine_ajustment == 0)
		{
			_timer.SetCounterPeriodPreloadValue(_timer.CounterPeriod() - 1);
			_phase_fine_ajustment = -1;
		}
	}
	else
	{
		_timer.SetCounterPeriodPreloadValue(_timer.CounterPeriod() - _phase_fine_ajustment);
		_phase_fine_ajustment = 0;
	}
}
