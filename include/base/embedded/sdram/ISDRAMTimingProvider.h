#pragma once
#include "base/unit/MHz.h"
#include "sdram_timing.h"

namespace base::sdram
{
	///
	/// @brief SDRAM 时序提供者。
	///
	///
	class ISDRAMTimingProvider
	{
	public:
		virtual ~ISDRAMTimingProvider() = default;

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
		virtual base::sdram::sdram_timing GetTiming(base::unit::MHz const &clk_frequency) const = 0;
	};

} // namespace base::sdram
