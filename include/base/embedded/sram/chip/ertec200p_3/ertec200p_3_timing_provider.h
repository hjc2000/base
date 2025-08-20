#pragma once
#include "base/embedded/sram/ISRAMTimingProvider.h"

namespace base
{
	namespace asynchronous_sram
	{
		namespace chip
		{
			namespace ertec200p_3
			{
				class ertec200p_3_timing_provider final :
					public base::asynchronous_sram::ISRAMTimingProvider
				{
				public:
					///
					/// @brief 获取指定 CLK 频率下的时序。
					///
					/// @param clk_frequency
					/// @return
					///
					virtual base::asynchronous_sram::asynchronous_sram_timing GetTiming(base::unit::MHz const &clk_frequency) const override
					{
						base::asynchronous_sram::asynchronous_sram_timing ret{};
						ret.set_clock_frequency(base::unit::MHz{168});
						ret.set_address_setup_clock_cycle_count(15);
						ret.set_address_hold_clock_cycle_count(15);
						ret.set_data_setup_clock_cycle_count(15);
						ret.set_bus_turn_around_clock_cycle_count(15);
						ret.set_clock_frequency(clk_frequency);
						return ret;
					}
				};

			} // namespace ertec200p_3
		} // namespace chip
	} // namespace asynchronous_sram
} // namespace base
