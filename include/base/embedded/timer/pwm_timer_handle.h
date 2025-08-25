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
		/// @brief 定时器输出 PWM 一个周期的计数值。
		///
		/// @param self
		/// @return
		///
		uint32_t cycle(base::pwm_timer::pwm_timer_handle const &self);

		///
		/// @brief PWM 占空时间。
		///
		/// @note 即：
		/// 	占空比 * cycle = duty.
		///
		/// @param self
		/// @return
		///
		uint32_t duty(base::pwm_timer::pwm_timer_handle const &self);

		///
		/// @brief 设置 PWM 占空时间。
		///
		/// @param self
		/// @param duty
		///
		void set_duty(base::pwm_timer::pwm_timer_handle &self, uint32_t duty);

	} // namespace pwm_timer
} // namespace base
