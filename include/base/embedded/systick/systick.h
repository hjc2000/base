#pragma once
#include "base/define.h"
#include "base/unit/MHz.h"
#include "base/unit/Nanosecond.h"
#include "base/unit/Second.h"
#include <chrono>
#include <cstdint>

namespace base
{
	namespace systick
	{
		///
		/// @brief 获取当前频率。
		///
		/// @return
		///
		base::unit::MHz frequency();

		///
		/// @brief 获取当前的计数值。
		///
		/// @note systick 被认为是减计数的。如果实际上是增计数的，可以将本函数实现为返回计数最大值减去
		/// 当前值，这样就虚拟成减计数的了。
		///
		/// @return
		///
		uint64_t current_value();

		///
		/// @brief 计数器的重装载值。
		///
		/// @note 计数器减计数到 0 后，下一个时钟周期会重新变成 reload_value 的值。
		///
		/// @return
		///
		uint64_t reload_value();

		///
		/// @brief 定时时间到处理函数。
		///
		/// @warning 实现者需要将本函数实现为线程安全和可重入。
		/// 	@note 最简单的方法就是在本函数的操作期间禁用全局中断。
		/// 	@note 最佳实践是只禁用 systick 的中断。
		///
		/// @warning 不要在中断函数中调用本函数。永远只能在主程序中调用本函数。
		///
		/// @param func
		///
		void set_elapsed_handler(std::function<void()> func);

		///
		/// @brief 系统时间戳。
		///
		/// @return
		///
		base::unit::Nanosecond system_time_stamp();

		/* #region 延时函数 */

		///
		/// @brief 循环中检测 current_value 的值来判断是否超时，从而进行延时。
		///
		/// @param value 要延时多少个 systick 的计数值。
		///
		IMPLEMENTED
		void delay_for_ticks(uint64_t value);

		IMPLEMENTED
		void delay(std::chrono::nanoseconds const &value);

		IMPLEMENTED
		void delay(std::chrono::microseconds const &value);

		IMPLEMENTED
		void delay(std::chrono::milliseconds const &value);

		IMPLEMENTED
		void delay(std::chrono::seconds const &value);

		IMPLEMENTED
		void delay(base::unit::Nanosecond const &value);

		IMPLEMENTED
		void delay(base::unit::Second const &value);

		/* #endregion */

	} // namespace systick
} // namespace base
