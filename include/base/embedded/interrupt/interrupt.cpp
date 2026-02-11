#include "interrupt.h" // IWYU pragma: keep

#if !HAS_THREAD

namespace
{
	int32_t volatile _global_interrupt_disable_times = 0;
}

void base::interrupt::disable_global_interrupt_recursive() noexcept
{
	disable_global_interrupt();
	_global_interrupt_disable_times = _global_interrupt_disable_times + 1;
}

void base::interrupt::enable_global_interrupt_recursive() noexcept
{
	disable_global_interrupt();
	_global_interrupt_disable_times = _global_interrupt_disable_times - 1;
	if (_global_interrupt_disable_times <= 0)
	{
		_global_interrupt_disable_times = 0;
		enable_global_interrupt();
	}
}

#endif // HAS_THREAD
