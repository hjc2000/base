#pragma once
#include <cstdint>

namespace base::interrupt
{
	void disable_global_interrupt_recursive() noexcept;
	void enable_global_interrupt_recursive() noexcept;

	class InterruptContext
	{
	private:
		friend void disable_global_interrupt_recursive() noexcept;
		friend void enable_global_interrupt_recursive() noexcept;

		inline static int32_t volatile _global_interrupt_disable_times = 0;

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
	};

	base::interrupt::InterruptContext &context();

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

	/* #region 递归禁用，使能全局中断 */

	///
	/// @brief 递归地禁用全局中断。
	///
	///
	inline void disable_global_interrupt_recursive() noexcept
	{
		context().disable_global_interrupt();
		context()._global_interrupt_disable_times = context()._global_interrupt_disable_times + 1;
	}

	///
	/// @brief 递归地使能全局中断。
	///
	///
	inline void enable_global_interrupt_recursive() noexcept
	{
		context().disable_global_interrupt();
		context()._global_interrupt_disable_times = context()._global_interrupt_disable_times - 1;

		if (context()._global_interrupt_disable_times <= 0)
		{
			context()._global_interrupt_disable_times = 0;
			context().enable_global_interrupt();
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

} // namespace base::interrupt
