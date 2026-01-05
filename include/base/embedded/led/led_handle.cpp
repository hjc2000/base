#include "led_handle.h"

void base::led::set_state(base::led::led_handle &h, base::led::State value)
{
	if (value == base::led::State::On)
	{
		turn_on(h);
	}
	else
	{
		turn_off(h);
	}
}
