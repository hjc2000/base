#include "sdram_timing.h"

base::sdram::sdram_timing::sdram_timing(int64_t row_count,
										base::MHz const &clock_frequency,
										base::Nanoseconds const &t_rsc,
										base::Nanoseconds const &t_xsr,
										base::Nanoseconds T_RAS,
										base::Nanoseconds T_RC,
										base::Nanoseconds T_WR,
										base::Nanoseconds T_RP,
										base::Nanoseconds T_RCD,
										base::Nanoseconds T_REF,
										int cas_latency)
{
	_row_count = row_count;

	{
		_clock_frequency = clock_frequency;
		_clock_period = base::Nanoseconds{_clock_frequency};
	}

	{
		_t_rsc = t_rsc;

		base::Fraction value{_t_rsc / _clock_period};
		_t_rsc_clock_count = static_cast<int>(value.Ceil());
	}

	{
		_t_xsr = t_xsr;

		base::Fraction value{_t_xsr / _clock_period};
		_t_xsr_clock_count = static_cast<int>(value.Ceil());
	}

	{
		_t_ras = T_RAS;

		base::Fraction value{_t_ras / clock_period()};
		_t_ras_clock_count = static_cast<int>(value.Ceil());
	}

	{
		_t_rc = T_RC;

		base::Fraction value{_t_rc / clock_period()};
		_t_rc_clock_count = static_cast<int>(value.Ceil());
	}

	{
		_t_wr = T_WR;

		base::Fraction value{_t_wr / clock_period()};
		_t_wr_clock_count = static_cast<int>(value.Ceil());
	}

	{
		_t_rp = T_RP;

		base::Fraction value{_t_rp / clock_period()};
		_t_rp_clock_count = static_cast<int>(value.Ceil());
	}

	{
		_t_ref = T_REF;

		base::Fraction value{_t_ref / clock_period()};
		_t_ref_clock_count = static_cast<int>(value.Ceil());
	}

	{
		_t_rcd = T_RCD;

		base::Fraction value{_t_rcd / clock_period()};
		_t_rcd_clock_count = static_cast<int>(value.Ceil());
	}

	_cas_latency = cas_latency;
}

base::Json base::sdram::sdram_timing::ToJson() const
{
	base::Json root{
		{"row_count", row_count()},
		{"clock_frequency", clock_frequency().ToString()},
		{"clock_period", clock_period().ToString()},
		{"t_rsc_clock_count", t_rsc_clock_count()},
		{"t_xsr_clock_count", t_xsr_clock_count()},
		{"t_ras_clock_count", t_ras_clock_count()},
		{"t_rc_clock_count", t_rc_clock_count()},
		{"t_wr_clock_count", t_wr_clock_count()},
		{"t_rp_clock_count", t_rp_clock_count()},
		{"t_rcd_clock_count", t_rcd_clock_count()},
		{"t_ref_clock_count", t_ref_clock_count()},
		{"auto_refresh_command_clock_count", auto_refresh_command_clock_count()},
		{"cas_latency", cas_latency()},
	};

	return root;
}
