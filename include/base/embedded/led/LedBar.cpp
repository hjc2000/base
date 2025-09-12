#include "LedBar.h" // IWYU pragma: keep
#include "base/embedded/SingletonProvider.h"

#if HAS_THREAD

base::led::LedBar &base::led::led_bar()
{
	static base::led::LedBar instance{};
	return instance;
}

#else

namespace
{
	base::embedded::SingletonProvider<base::led::LedBar> _led_bar_instance_provider{};

} // namespace

base::led::LedBar &base::led::led_bar()
{
	return _led_bar_instance_provider.Instance();
}

#endif // HAS_THREAD
