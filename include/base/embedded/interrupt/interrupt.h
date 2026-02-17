#pragma once
#include "base/define.h"
#include <cstdint>

namespace base::interrupt
{
	class GlobalInterruptionGuard;

	class DisableGlobalInterruptionImpelement
	{
	private:
		AS_STATIC_CLASS(DisableGlobalInterruptionImpelement)

		friend class GlobalInterruptionGuard;

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

		/* #endregion */
	};

	///
	/// @brief 禁用指定的中断。
	///
	/// @param irq 中断号。
	///
	void disable_interrupt(int32_t irq) noexcept;

	///
	/// @brief 使能指定的中断。不指定优先级，保持默认优先级。
	///
	/// @param irq 中断号。
	///
	void enable_interrupt(int32_t irq) noexcept;

	///
	/// @brief 使能指定的中断并指定优先级。
	///
	/// @param irq 中断号。
	/// @param priority 优先级。
	///
	void enable_interrupt(int32_t irq, int32_t priority) noexcept;

	///
	/// @brief 构造时禁用全局中断，析构时使能全局中断。
	///
	class GlobalInterruptionGuard
	{
	public:
		GlobalInterruptionGuard()
		{
			DisableGlobalInterruptionImpelement::disable_global_interrupt_recursive();
		}

		~GlobalInterruptionGuard()
		{
			DisableGlobalInterruptionImpelement::enable_global_interrupt_recursive();
		}
	};

} // namespace base::interrupt
