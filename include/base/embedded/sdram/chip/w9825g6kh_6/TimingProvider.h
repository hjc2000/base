#pragma once
#include "base/embedded/sdram/ISDRAMTimingProvider.h"

namespace base
{
	namespace sdram
	{
		namespace chip
		{
			namespace w9825g6kh_6
			{
				class TimingProvider :
					public base::sdram::ISDRAMTimingProvider
				{
				public:
					///
					/// @brief 允许的最大时钟频率。
					///
					/// @return base::MHz
					///
					virtual base::MHz MaxClockFrequency() const override
					{
						return base::MHz{166};
					}

					///
					/// @brief 获取指定时钟频率下的时序。
					///
					/// @param clock_frequency
					/// @return base::sdram::sdram_timing
					///
					virtual base::sdram::sdram_timing GetTiming(base::MHz const &clock_frequency) const override
					{
						base::Nanoseconds clock_period{clock_frequency};

						base::sdram::sdram_timing ret{};
						ret.set_row_count(8192);
						ret.set_clock_frequency(clock_frequency);
						ret.set_t_rsc(2 * clock_period);
						ret.set_t_xsr(base::Nanoseconds{72});
						ret.set_t_ras(base::Nanoseconds{42});
						ret.set_t_rc(base::Nanoseconds{60});
						ret.set_t_wr(2 * clock_period);
						ret.set_t_rp(base::Nanoseconds{15});
						ret.set_t_rcd(base::Nanoseconds{15});

						// 提前 10ms 刷新
						ret.set_t_ref(base::Nanoseconds{std::chrono::milliseconds{64 - 10}});

						if (clock_frequency > base::MHz{133})
						{
							ret.set_cas_latency(3);
						}
						else
						{
							ret.set_cas_latency(2);
						}

						return ret;
					}
				};
			} // namespace w9825g6kh_6
		} // namespace chip
	} // namespace sdram
} // namespace base
