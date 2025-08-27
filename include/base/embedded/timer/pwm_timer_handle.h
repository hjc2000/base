#pragma once
#include "base/unit/Hz.h"
#include <cstdint>
#include <memory>

namespace base
{
	namespace pwm_timer
	{
		///
		/// @brief PWM 定时器句柄。
		///
		/// @note PWM 定时器可以输出 PWM.
		///
		/// @note 输出分为 2 个状态，对应 2 个极性的电平。分别为 “有效状态”，“无效状态”。
		/// 有效状态和无效状态的电平可以设置。例如可以设置有效状态为高电平，无效状态为低电平，
		/// 也可以设置有效状态为低电平，无效状态为高电平。
		/// 	@li 控制 NPN 三极管时，PWM 输出连接到基极，射极接地，此时应该设置有效状态为高电平，
		/// 		无效状态为低电平。
		/// 	@li 控制共阳极的 LED 灯，PWM 输出接到 LED 灯的阴极，此时应该设置有效状态为低电平，
		/// 		无效状态为高电平。
		///
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
		/// @note 实现者需要将硬件抽象为符合下面介绍的特性。
		///
		/// @note 刚开始的时候当前计数值是 0.
		///
		/// 计数值小于 compare_value 时输出有效，计数值增大到等于 compare_value 时，输出立刻
		/// 变为无效状态。
		///
		/// 如果 compare_value 等于 0, 则一开始输出就是无效状态，此时占空比为 0.
		///
		/// compare_value 大于计数器的计数最大值，即大于等于计数器周期时，计数值永远小于 compare_value,
		/// 此时占空比为 100%.
		///
		/// @note 例如计数周期是 256, 设置 compare_value 为 256 / 8 = 128.
		///
		/// 刚开始计数值为 0, 小于 compare_value, 输出有效。
		///
		/// 计数值增大到 compare_value = 128 时，输出变无效。则计数值为 [0, 128) 的时间段内，输出有效。
		/// 一共持续 128 - 0 = 128 个计数。
		///
		/// 计数值继续增大，增大到 255 后，下一个时钟周期到来，继续递增，溢出变成 0, 再次小于 compare_value,
		/// 输出重新变成有效。则在 [128, 256) 的时间段内，输出无效。一共持续 256 - 128 = 128 个计数。
		///
		/// 所以占空比为 50%.
		///
		///
		/// @param self
		/// @param frequency PWM 的频率。
		///
		void initialize_as_up_mode(base::pwm_timer::pwm_timer_handle &self,
								   base::unit::Hz const &frequency);

		///
		/// @brief 初始化为递减计数模式。
		///
		/// @note 刚开始的时候当前计数值是重装载值。
		///
		/// @note compare_value 小于当前计数值的时候输出是无效状态，输出与无效电平。
		///
		/// @note 计数值递减到等于 compare_value 的时候，输出立刻切换为有效状态，输出有效电平。
		///
		/// @param self
		/// @param frequency
		///
		void initialize_as_down_mode(base::pwm_timer::pwm_timer_handle &self,
									 base::unit::Hz const &frequency);

		///
		/// @brief 初始化为先向上计数再向下计数的模式。
		///
		/// @param self
		/// @param frequency
		///
		void initialize_as_up_down_mode(base::pwm_timer::pwm_timer_handle &self,
										base::unit::Hz const &frequency);

		///
		/// @brief 计数器一次单调计数的长度。
		///
		/// @note 初始化完定时器的核心后就可以读取本属性了。
		///
		/// @note 对于增计数模式，计数器从 0 计数到 counter_period - 1.
		/// @note 对于减计数模式，计数器从 counter_period - 1 计数到 0.
		/// @note 对于增减计数模式，计数器从 0 计数到 counter_period, 然后递减计数到 0.
		///
		/// @param self
		/// @return
		///
		uint32_t counter_period(base::pwm_timer::pwm_timer_handle const &self);

		///
		/// @brief 配置输出。
		///
		/// @param self
		/// @param channel_id 要配置的通道的 ID.
		/// @param effective_polarity 有效极性。
		/// @param compare_value 比较寄存器的比较值。
		///
		/// @param dead_time 同一相的一对互相反相的输出，在一个输出变成无效后，经过死区时间后
		/// 另一个输出才会变成有效。这可以避免全桥 PWM 控制的同一相 IGBT 同时导通造成短路。
		///
		void configure_output(base::pwm_timer::pwm_timer_handle &self,
							  uint32_t channel_id,
							  base::pwm_timer::Polarity effective_polarity,
							  uint32_t compare_value,
							  uint32_t dead_time);

		///
		/// @brief 启动定时器，开始输出 PWM 信号。
		///
		/// @param self
		/// @param channel_id
		///
		void start(base::pwm_timer::pwm_timer_handle &self, uint32_t channel_id);

		///
		/// @brief 启动定时器，并同时启动所有通道的输出。
		///
		/// @param self
		///
		void start_all_channels(base::pwm_timer::pwm_timer_handle &self);

		///
		/// @brief 停止指定通道的 PWM 输出。
		///
		/// @note 停止后该通道输出无效电平。
		///
		/// @param self
		/// @param channel_id
		///
		void stop(base::pwm_timer::pwm_timer_handle &self, uint32_t channel_id);

		///
		/// @brief 停止所有通道的 PWM 输出。
		///
		/// @param self
		///
		void stop_all_channels(base::pwm_timer::pwm_timer_handle &self);

		///
		/// @brief 运行时改变比较值。
		///
		/// @param self
		/// @param channel_id
		/// @param value
		///
		void change_compare_value(base::pwm_timer::pwm_timer_handle &self,
								  uint32_t channel_id,
								  uint32_t value);

		///
		/// @brief PWM 定时器的底层初始化回调。
		///
		/// @param id
		///
		void msp_initialize_callback(uint32_t id);

	} // namespace pwm_timer
} // namespace base
