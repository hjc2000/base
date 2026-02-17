#pragma once
#include "base/define.h"
#include <cstdint>

namespace base
{
	class interrupt
	{
	private:
		DELETE_COPY_AND_MOVE(interrupt);

		inline static int32_t volatile _global_interrupt_disable_times = 0;

		///
		/// @brief 禁用全局中断。
		///
		///
		static void disable_global_interrupt() noexcept;

		///
		/// @brief 使能全局中断。
		///
		///
		static void enable_global_interrupt() noexcept;

	public:
		///
		/// @brief 禁用指定的中断。
		///
		/// @param irq 中断号。
		///
		static void disable_interrupt(int32_t irq) noexcept;

		///
		/// @brief 使能指定的中断。不指定优先级，保持默认优先级。
		///
		/// @param irq 中断号。
		///
		static void enable_interrupt(int32_t irq) noexcept;

		///
		/// @brief 使能指定的中断并指定优先级。
		///
		/// @param irq 中断号。
		/// @param priority 优先级。
		///
		static void enable_interrupt(int32_t irq, int32_t priority) noexcept;

		/* #region 递归禁用，使能全局中断 */

		///
		/// @brief 递归地禁用全局中断。
		///
		///
		static void disable_global_interrupt_recursive() noexcept
		{
			disable_global_interrupt();
			_global_interrupt_disable_times = _global_interrupt_disable_times + 1;
		}

		///
		/// @brief 递归地使能全局中断。
		///
		///
		static void enable_global_interrupt_recursive() noexcept
		{
			disable_global_interrupt();
			_global_interrupt_disable_times = _global_interrupt_disable_times - 1;

			if (_global_interrupt_disable_times <= 0)
			{
				_global_interrupt_disable_times = 0;
				enable_global_interrupt();
			}
		}

		///
		/// @brief 构造时禁用全局中断，析构时使能全局中断。
		///
		class GlobalInterruptionGuard
		{
		public:
			GlobalInterruptionGuard()
			{
				disable_global_interrupt_recursive();
			}

			~GlobalInterruptionGuard()
			{
				enable_global_interrupt_recursive();
			}
		};

		/* #endregion */
	};

} // namespace base
