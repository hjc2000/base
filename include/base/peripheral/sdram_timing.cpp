#include "sdram_timing.h"

base::Json base::sdram::sdram_timing::ToJson() const
{
	base::Json root{
		{"row_count", row_count()},
		{"clock_frequency", clock_frequency().ToString()},
		{"clock_period", clock_period().ToString()},
		{"T_RSC_CLK_Count", T_RSC_CLK_Count()},
		{"T_XSR_CLK_Count", T_XSR_CLK_Count()},
		{"T_RAS_CLK_Count", T_RAS_CLK_Count()},
		{"T_RC_CLK_Count", T_RC_CLK_Count()},
		{"T_WR_CLK_Count", T_WR_CLK_Count()},
		{"T_RP_CLK_Count", T_RP_CLK_Count()},
		{"T_RCD_CLK_Count", T_RCD_CLK_Count()},
		{"T_REF_CLK_Count", T_REF_CLK_Count()},
		{"auto_refresh_command_clock_count", auto_refresh_command_clock_count()},
		{"cas_latency", cas_latency()},
	};

	return root;
}
