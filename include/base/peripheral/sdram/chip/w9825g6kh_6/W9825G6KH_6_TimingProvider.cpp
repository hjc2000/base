#include "W9825G6KH_6_TimingProvider.h"

base::sdram::sdram_timing base::sdram::W9825G6KH_6_TimingProvider::GetTiming(base::MHz const &clock_frequency) const
{
	base::Nanoseconds clock_period{clock_frequency};

	// 计算时序时，很多地方额外加了一个 clock_period，这是为了提供更加保守的时序。
	base::sdram::sdram_timing ret{};
	ret.set_row_count(8192);
	ret.set_clock_frequency(clock_frequency);
	ret.set_t_rsc(2 * clock_period + clock_period);
	ret.set_t_xsr(base::Nanoseconds{72} + clock_period);
	ret.set_t_ras(base::Nanoseconds{42} + clock_period);
	ret.set_t_rc(base::Nanoseconds{60} + clock_period);
	ret.set_t_wr(2 * clock_period + clock_period);
	ret.set_t_rp(base::Nanoseconds{15} + clock_period);
	ret.set_t_rcd(base::Nanoseconds{15} + clock_period);

	// 提前 10ms 刷新
	ret.set_t_ref(base::Nanoseconds{std::chrono::milliseconds{64 - 10}});

	if (clock_frequency > base::MHz{133})
	{
		ret.set_cas_latency(3);
	}
	else
	{
		// 为了保险，始终使用 3，不知道怎么回事，家里的开发板用 2 一跑就崩。
		ret.set_cas_latency(3);
	}

	return ret;
}
