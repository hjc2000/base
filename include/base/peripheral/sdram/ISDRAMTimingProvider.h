#pragma once
#include "base/unit/MHz.h"
#include "sdram_timing.h"

namespace base
{
	namespace sdram
	{
		///
		/// @brief SDRAM 时序提供者。
		///
		///
		class ISDRAMTimingProvider
		{
		public:
			///
			/// @brief 允许的最大时钟频率。
			///
			/// @return
			///
			virtual base::MHz MaxClockFrequency() const = 0;

			///
			/// @brief 获取指定 CLK 频率下的时序。
			///
			/// @param clk_frequency
			/// @return
			///
			virtual base::sdram::sdram_timing GetTiming(base::MHz const &clk_frequency) const = 0;
		};

	} // namespace sdram
} // namespace base
