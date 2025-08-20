#pragma once
#include "asynchronous_sram_timing.h"
#include "base/unit/MHz.h"

namespace base
{
	namespace asynchronous_sram
	{
		class ISRAMTimingProvider
		{
		public:
			virtual ~ISRAMTimingProvider() = default;

			///
			/// @brief 允许的最大时钟频率。
			///
			/// @return
			///
			virtual base::unit::MHz MaxClockFrequency() const = 0;

			///
			/// @brief 获取指定 CLK 频率下的时序。
			///
			/// @param clk_frequency
			/// @return
			///
			virtual base::asynchronous_sram::asynchronous_sram_timing GetTiming(base::unit::MHz const &clk_frequency) const = 0;
		};

	} // namespace asynchronous_sram
} // namespace base
