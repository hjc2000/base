#pragma once
#include "base/embedded/timer/InputCaptureTimer.h"
#include "base/math/InertialElement.h"
#include "base/math/PID.h"
#include <cstdint>

namespace base
{
	class InputCaptureTimerPll
	{
	private:
		base::input_capture_timer::InputCaptureTimer &_timer;
		int64_t _frequency_multiple = 1;
		int64_t _expected_capture_value{};

		int64_t _additional_capture_period = 0;

		int64_t _current_capture_register_value{};
		int64_t _last_capture_value{};
		int64_t _current_capture_value{};
		int64_t _captured_signal_period{};

		base::InertialElement _captured_signal_period_filter{};

		///
		/// @brief 锁频环 PID.
		///
		///
		base::PID _fll_pid{};
		int64_t _frequency_error{};

		int64_t _phase_error{};
		int64_t _phase_ajustment{};

		int64_t _phase_fine_error{};
		int64_t _phase_fine_ajustment{};

		bool _adjust_started = false;

		void LockFrequency();
		void LockPhase();

	public:
		InputCaptureTimerPll(base::input_capture_timer::InputCaptureTimer &timer,
							 int64_t frequency_multiple,
							 int64_t expected_capture_value);

		void UpdateCaptureValue(int64_t capture_value);

		void OnPeriodElapsed();

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
		/// @brief 当前捕获寄存器的值。
		///
		/// @return
		///
		int64_t CurrentCaptureRegisterValue() const
		{
			return _current_capture_register_value;
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

		///
		/// @brief 频率误差。
		///
		/// @return 返回值不是单位为 Hz 的频率。返回值是计数器的计数值的误差。
		///
		int64_t FrequencyError() const
		{
			return _frequency_error;
		}

		///
		/// @brief 相位误差。
		///
		/// @return
		///
		int64_t PhaseError() const
		{
			return _phase_error;
		}
	};

} // namespace base
