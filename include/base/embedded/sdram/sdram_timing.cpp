#include "sdram_timing.h"

base::Json base::sdram::sdram_timing::ToJson() const
{
	base::Json root{
		{"row_count", row_count()},
		{"clock_frequency", clock_frequency().ToString()},
		{"clock_cycle", clock_cycle().ToString()},
		{"t_rsc_clock_cycle_count", t_rsc_clock_cycle_count()},
		{"t_xsr_clock_cycle_count", t_xsr_clock_cycle_count()},
		{"t_ras_clock_cycle_count", t_ras_clock_cycle_count()},
		{"t_rc_clock_cycle_count", t_rc_clock_cycle_count()},
		{"t_wr_clock_cycle_count", t_wr_clock_cycle_count()},
		{"t_rp_clock_cycle_count", t_rp_clock_cycle_count()},
		{"t_rcd_clock_cycle_count", t_rcd_clock_cycle_count()},
		{"t_ref_clock_cycle_count", t_ref_clock_cycle_count()},
		{"auto_refresh_command_clock_cycle_count", auto_refresh_command_clock_cycle_count()},
		{"cas_latency", cas_latency()},
	};

	return root;
}
