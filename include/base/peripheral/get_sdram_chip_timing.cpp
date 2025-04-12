#include "get_sdram_chip_timing.h"
#include "base/string/define.h"
#include "base/unit/MHz.h"
#include "base/unit/Nanoseconds.h"
#include "sdram_timing.h"
#include <stdexcept>

base::sdram::sdram_timing base::sdram::get_w9825g6kh_6_timing(base::MHz const &clock_frequency)
{
	if (clock_frequency > base::MHz{166})
	{
		throw std::invalid_argument{CODE_POS_STR + "时钟频率过高。"};
	}

	base::Nanoseconds clock_period{clock_frequency};

	base::sdram::sdram_timing ret{};
	ret._row_count = 8192;
	ret._clock_frequency = clock_frequency;
	ret._t_rsc = 2 * clock_period + clock_period;
	ret._t_xsr = base::Nanoseconds{72} + clock_period;
	ret._t_ras = base::Nanoseconds{42} + clock_period;
	ret._t_rc = base::Nanoseconds{60} + clock_period;
	ret._t_wr = 2 * clock_period + clock_period;
	ret._t_rp = base::Nanoseconds{15} + clock_period;
	ret._t_rcd = base::Nanoseconds{15} + clock_period;

	ret._t_ref = base::Nanoseconds{std::chrono::milliseconds{64}} -
				 base::Nanoseconds{std::chrono::milliseconds{10}};

	if (clock_frequency > base::MHz{133})
	{
		ret._cas_latency = 3;
	}
	else
	{
		// 为了保险，始终使用 3，不知道怎么回事，家里的开发板用 2 一跑就崩。
		ret._cas_latency = 3;
	}

	return ret;
}
