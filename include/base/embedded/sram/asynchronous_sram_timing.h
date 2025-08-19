#pragma once

#include "base/unit/Nanosecond.h"

namespace base
{
	namespace asynchronous_sram
	{
		///
		/// @brief 异步的 SRAM 时序。
		///
		/// @note 异步 SRAM 不需要主机提供时钟信号，但是需要主机接口支持 WAIT 信号。
		///
		///
		class asynchronous_sram_timing
		{
		private:
			base::unit::Nanosecond _address_setup_time{};
			base::unit::Nanosecond _address_hold_time{};
			base::unit::Nanosecond _data_setup_time{};
			base::unit::Nanosecond _data_hold_time{};
			base::unit::Nanosecond _bus_turn_around_time{};

		public:
		};

	} // namespace asynchronous_sram
} // namespace base
