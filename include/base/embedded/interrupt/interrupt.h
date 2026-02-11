#pragma once
#include "base/define.h"
#include <cstdint>

namespace base::interrupt
{
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
	/// @brief 禁用全局中断。
	///
	///
	void disable_global_interrupt() noexcept;

	///
	/// @brief 使能全局中断。
	///
	///
	void enable_global_interrupt() noexcept;

	/* #region 递归禁用，使能全局中断 */

	///
	/// @brief 递归地禁用全局中断。
	///
	///
	IMPLEMENTED
	void disable_global_interrupt_recursive() noexcept;

	///
	/// @brief 递归地使能全局中断。
	///
	///
	IMPLEMENTED
	void enable_global_interrupt_recursive() noexcept;

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

} // namespace base::interrupt
