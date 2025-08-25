#pragma once
#include "base/unit/Hz.h"
#include <cstdint>
#include <memory>

namespace base
{
	namespace pwm_timer
	{
		enum class Polarity
		{
			Positive,
			Negative,
		};

		class pwm_timer_handle;

		std::shared_ptr<base::pwm_timer::pwm_timer_handle> open(uint32_t id);

		void initialize_as_up_count_mode(base::pwm_timer::pwm_timer_handle &self,
										 base::unit::Hz const &frequency,
										 base::pwm_timer::Polarity polarity);

		///
		/// @brief 定时器输出 PWM 一个周期的计数次数。
		///
		/// @param self
		/// @return
		///
		uint32_t cycle(base::pwm_timer::pwm_timer_handle const &self);

		///
		/// @brief 比较值。
		///
		/// @note 计数值变化到等于比较值的时候，输出极性会立刻变化。
		///
		/// @param self
		/// @return
		///
		uint32_t compare_value(base::pwm_timer::pwm_timer_handle const &self);

		///
		/// @brief 设置比较值。
		///
		/// @param self
		/// @param value
		///
		void set_compare_value(base::pwm_timer::pwm_timer_handle &self, uint32_t value);

		///
		/// @brief 启动定时器，开始输出 PWM 信号。
		///
		/// @param self
		///
		void start(base::pwm_timer::pwm_timer_handle &self);

	} // namespace pwm_timer
} // namespace base
