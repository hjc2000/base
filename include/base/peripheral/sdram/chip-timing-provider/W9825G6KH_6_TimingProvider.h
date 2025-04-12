#pragma once
#include "base/peripheral/sdram/ISDRAMTimingProvider.h"

namespace base
{
	namespace sdram
	{
		class W9825G6KH_6_TimingProvider :
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
			virtual base::sdram::sdram_timing GetTiming(base::MHz const &clock_frequency) const override;
		};

	} // namespace sdram
} // namespace base
