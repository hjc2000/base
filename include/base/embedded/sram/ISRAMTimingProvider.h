#pragma once
#include "asynchronous_sram_timing.h"
#include "base/unit/MHz.h"

namespace base
{
	namespace asynchronous_sram
	{
		///
		/// @brief 异步 SRAM 的时序提供者。
		///
		///
		class ISRAMTimingProvider
		{
		public:
			virtual ~ISRAMTimingProvider() = default;

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
