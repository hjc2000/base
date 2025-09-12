#include "LedBar.h" // IWYU pragma: keep
#include "base/task/task.h"
#include <cstdint>

#if HAS_THREAD

base::led::LedBar &base::led::led_bar()
{
	static base::led::LedBar instance{};
	return instance;
}

#else

namespace
{
	struct
	{
		bool _initialized = false;
		alignas(base::led::LedBar) uint8_t _led_bar_obj_buffer[sizeof(base::led::LedBar)];
	} _led_bar_obj_provider;

} // namespace

base::led::LedBar &base::led::led_bar()
{
	if (!_led_bar_obj_provider._initialized)
	{
		base::task::TaskSchedulerSuspendGuard g{};
		if (!_led_bar_obj_provider._initialized)
		{
			new (_led_bar_obj_provider._led_bar_obj_buffer) base::led::LedBar{};
			_led_bar_obj_provider._initialized = true;
		}
	}

	return *reinterpret_cast<base::led::LedBar *>(_led_bar_obj_provider._led_bar_obj_buffer);
}

#endif // HAS_THREAD
