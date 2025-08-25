#pragma once
#include "base/unit/Hz.h"
#include <cstdint>
#include <memory>

namespace base
{
	namespace pwm_timer
	{
		class pwm_timer_handle;

		std::shared_ptr<base::pwm_timer::pwm_timer_handle> open(uint32_t id);

		void initialize(base::pwm_timer::pwm_timer_handle &self,
						base::unit::Hz const &frequency);

		///
		/// @brief 获取一个整数，代表了 PWM 的周期。
		///
		/// @param self
		/// @return
		///
		uint32_t cycle(base::pwm_timer::pwm_timer_handle const &self);

		///
		/// @brief 获取一个整数，代表了 PWM 的占空。
		/// 即：
		/// 	占空比 * cycle = duty.
		///
		/// @param self
		/// @return
		///
		uint32_t duty(base::pwm_timer::pwm_timer_handle const &self);

	} // namespace pwm_timer
} // namespace base
