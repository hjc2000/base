#include "LedBar.h" // IWYU pragma: keep

namespace
{
	base::led::LedBar _led_bar{};
}

base::led::LedBar &base::led::GlobalLedBar()
{
	return _led_bar;
}
