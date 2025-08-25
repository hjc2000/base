#pragma once
#include "base/unit/Hz.h"
#include <cstdint>
#include <memory>

namespace base
{
	namespace pwm_timer
	{
		class pwm_timer_handle;

		enum class Polarity
		{
			Positive,
			Negative,
		};

		std::shared_ptr<base::pwm_timer::pwm_timer_handle> open(uint32_t id);

		///
		/// @brief 初始化为增计数模式。
		///
		/// @note 刚开始的时候当前计数值是 0.
		///
		/// @note compare_value 大于当前计数值的时候输出是有效状态，输出 effective_polarity
		/// 设置的有效极性的电平。
		///
		/// @note 计数值递增到等于 compare_value 的时候输出就会立刻切换成无效状态，输出与
		/// effective_polarity 相反的的无效极性电平。
		///
		/// @note 例如计数周期是 256, 设置 compare_value 为 256 / 8 = 128.
		/// 设置 effective_polarity 为 Positive, 即输出有效状态是高电平。
		///
		/// @li 刚开始计数值等于 0, 比较值大于计数值，输出是有效状态，输出高电平。
		/// @li 计数值等于 compare_value = 128 的时候输出切换成无效状态，输出低电平。
		/// @li 计数值继续递增，递增到 255, 下一个时钟信号到来，计数值继续递增 1, 溢出清零的瞬间，
		/// 	当前计数值又满足小于 compare_value 了，输出变成有效状态，再次输出高电平。
		///
		/// 这样计数值属于 [0, 128) 的时候输出高电平，计数值属于 [128, 256) 的时候
		/// 输出低电平。高电平和低电平各占一半，占空比为 50%.
		///
		/// 注：
		/// 	这里的 [128, 256) 中的 256 不是指计数器的值真的能是 256, 指的是下一个周期的 0.
		///
		/// @param self
		/// @param frequency PWM 的频率。
		/// @param effective_polarity 有效极性。
		///
		void initialize_as_up_mode(base::pwm_timer::pwm_timer_handle &self,
								   base::unit::Hz const &frequency,
								   base::pwm_timer::Polarity effective_polarity);

		///
		/// @brief 初始化为递减计数模式。
		///
		/// @note 刚开始的时候当前计数值是重装载值。
		///
		/// @note compare_value 小于当前计数值的时候输出是无效状态，输出与 effective_polarity
		/// 极性相反的电平。
		///
		/// @note 计数值递减到等于 compare_value 的时候，输出立刻切换为有效状态，输出 effective_polarity
		/// 设置的有效电平。
		///
		/// @param self
		/// @param frequency
		/// @param effective_polarity
		///
		void initialize_as_down_mode(base::pwm_timer::pwm_timer_handle &self,
									 base::unit::Hz const &frequency,
									 base::pwm_timer::Polarity effective_polarity);

		///
		/// @brief 初始化为先向上计数再向下计数的模式。
		///
		/// @param self
		/// @param frequency
		/// @param effective_polarity
		///
		void initialize_as_up_down_mode(base::pwm_timer::pwm_timer_handle &self,
										base::unit::Hz const &frequency,
										base::pwm_timer::Polarity effective_polarity);

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
		/// @brief 死区时间。单位：定时器计数值。
		///
		/// @param self
		/// @return
		///
		uint32_t dead_time(base::pwm_timer::pwm_timer_handle const &self);

		///
		/// @brief 设置死区时间。单位：定时器计数值。
		///
		/// @param self
		/// @param value
		///
		void set_dead_time(base::pwm_timer::pwm_timer_handle &self, uint32_t value);

		///
		/// @brief 启动定时器，开始输出 PWM 信号。
		///
		/// @note 启动前必须设置好比较值和死区时间等，否则有的实现者可能选择抛出异常，
		/// 有的实现者可能选择使用默认值。
		///
		/// @param self
		///
		void start(base::pwm_timer::pwm_timer_handle &self);

		///
		/// @brief 停止定时器并停止 PWM 输出。
		///
		/// @note 所有输出都要置于无效的电平。
		///
		/// @param self
		///
		void stop(base::pwm_timer::pwm_timer_handle &self);

	} // namespace pwm_timer
} // namespace base
