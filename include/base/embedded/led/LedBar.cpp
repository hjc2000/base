#include "LedBar.h" // IWYU pragma: keep
#include "base/SingletonProvider.h"

namespace
{
	base::SingletonProvider<base::led::LedBar> _led_bar_instance_provider{};

} // namespace

base::led::LedBar &base::led::led_bar()
{
	return _led_bar_instance_provider.Instance();
}
