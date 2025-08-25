#pragma once
#include "base/unit/Hz.h"
#include <bitset>
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
		/// @note compare_value 大于当前计数值的时候输出是有效状态，输出有效极性的电平。
		///
		/// @note 计数值递增到等于 compare_value 的时候输出就会立刻切换成无效状态，
		/// 输出无效极性电平。
		///
		/// @note 例如计数周期是 256, 设置 compare_value 为 256 / 8 = 128.
		/// 设置有效极性为正，即输出有效状态是高电平。
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
		/// @brief 定时器一个周期的计数次数。
		///
		/// @note 初始化完定时器核心部分后，就可以知道定时器一个周期计数多少了。
		///
		/// @param self
		/// @return
		///
		uint32_t cycle(base::pwm_timer::pwm_timer_handle const &self);

		///
		/// @brief 配置输出。
		///
		/// @param self
		/// @param channels 配置要对哪一个通道生效，就把对应的位置 1.
		/// @param effective_polarity 有效极性。
		/// @param idle_polarity 空闲极性。
		/// @param compare_value 比较寄存器的比较值。
		///
		/// @param dead_time 同一相的一对互相反相的输出，在一个输出变成无效后，经过死区时间后
		/// 另一个输出才会变成有效。这可以避免全桥 PWM 控制的同一相 IGBT 同时导通造成短路。
		///
		void configure_output(base::pwm_timer::pwm_timer_handle &self,
							  std::bitset<32> const &channels,
							  base::pwm_timer::Polarity effective_polarity,
							  base::pwm_timer::Polarity idle_polarity,
							  uint32_t compare_value,
							  uint32_t dead_time);

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

		///
		/// @brief 运行时改变比较值。
		///
		/// @param self
		/// @param channels
		/// @param value
		///
		void change_compare_value(base::pwm_timer::pwm_timer_handle &self,
								  std::bitset<32> channels,
								  uint32_t value);

	} // namespace pwm_timer
} // namespace base
