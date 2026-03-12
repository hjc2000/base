#include "LedBar.h"
#include "base/GlobalObjectProvider.h"

namespace
{
	base::GlobalObjectProvider<base::led::LedBar> _led_bar_instance_provider{};

} // namespace

base::led::LedBar &base::led::led_bar()
{
	return _led_bar_instance_provider.Instance();
}
