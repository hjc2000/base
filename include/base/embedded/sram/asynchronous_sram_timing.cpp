#include "asynchronous_sram_timing.h" // IWYU pragma: keep
#include "base/string/Json.h"

base::Json base::asynchronous_sram::asynchronous_sram_timing::ToJson() const
{
	base::Json ret{
		{"clock_frequency", clock_frequency()},
		{"clock_cycle", clock_cycle()},
		{"address_setup_time", address_setup_time()},
		{"address_setup_clock_cycle_count", address_setup_clock_cycle_count()},
		{"address_hold_time", address_hold_time()},
		{"address_hold_clock_cycle_count", address_hold_clock_cycle_count()},
		{"data_setup_time", data_setup_time()},
		{"data_setup_clock_cycle_count", data_setup_clock_cycle_count()},
		{"bus_turn_around_time", bus_turn_around_time()},
		{"bus_turn_around_clock_cycle_count", bus_turn_around_clock_cycle_count()},
	};

	return ret;
}
