#pragma once
#include "base/embedded/sdram/ISDRAMTimingProvider.h"
#include "base/string/define.h"
#include <stdexcept>

namespace base::sdram::chip::w9825g6kh_6
{
	class TimingProvider final :
		public base::sdram::ISDRAMTimingProvider
	{
	public:
		///
		/// @brief 允许的最大时钟频率。
		///
		/// @return
		///
		virtual base::unit::MHz MaxClockFrequency() const override
		{
			return base::unit::MHz{166};
		}

		///
		/// @brief 获取指定时钟频率下的时序。
		///
		/// @param clock_frequency
		///
		/// @return
		///
		virtual base::sdram::sdram_timing GetTiming(base::unit::MHz const &clock_frequency) const override
		{
			if (clock_frequency > MaxClockFrequency())
			{
				throw std::invalid_argument{CODE_POS_STR + "频率过高。"};
			}

			base::unit::Nanosecond clock_period{clock_frequency};

			base::sdram::sdram_timing ret{};
			ret.set_row_count(8192);
			ret.set_clock_frequency(clock_frequency);
			ret.set_t_rsc(2 * clock_period);
			ret.set_t_xsr(base::unit::Nanosecond{72});
			ret.set_t_ras(base::unit::Nanosecond{42});
			ret.set_t_rc(base::unit::Nanosecond{60});
			ret.set_t_wr(2 * clock_period);
			ret.set_t_rp(base::unit::Nanosecond{15});
			ret.set_t_rcd(base::unit::Nanosecond{15});

			// 提前 10ms 刷新
			ret.set_t_ref(base::unit::Nanosecond{std::chrono::milliseconds{64 - 10}});

			if (clock_frequency > base::unit::MHz{133})
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

} // namespace base::sdram::chip::w9825g6kh_6
