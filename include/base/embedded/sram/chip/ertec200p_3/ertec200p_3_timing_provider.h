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
				private:
					base::asynchronous_sram::asynchronous_sram_timing _timing{};

				public:
					ertec200p_3_timing_provider()
					{
						// 先基于 168MHz 设置好时序。
						_timing.set_clock_frequency(base::unit::MHz{168});
						_timing.set_address_setup_clock_cycle_count(15);
						_timing.set_address_hold_clock_cycle_count(15);
						_timing.set_data_setup_clock_cycle_count(15);
						_timing.set_bus_turn_around_clock_cycle_count(15);
					}

					///
					/// @brief 获取指定 CLK 频率下的时序。
					///
					/// @param clk_frequency
					/// @return
					///
					virtual base::asynchronous_sram::asynchronous_sram_timing GetTiming(base::unit::MHz const &clk_frequency) const override
					{
						base::asynchronous_sram::asynchronous_sram_timing ret{_timing};

						// 改变控制器时钟周期，相应的各种时序的纳秒数不变，但是时钟周期数会改变，
						// 适应新的时钟频率。
						ret.set_clock_frequency(clk_frequency);
						return ret;
					}
				};

			} // namespace ertec200p_3
		} // namespace chip
	} // namespace asynchronous_sram
} // namespace base
