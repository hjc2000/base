#pragma once
#include "ISRAMTimingProvider.h"
#include <cstdint>
#include <memory>

namespace base
{
	namespace asynchronous_sram
	{
		class asynchronous_sram_controller_handle;

		std::shared_ptr<base::asynchronous_sram::asynchronous_sram_controller_handle> open(uint32_t id);

		void initialize(base::asynchronous_sram::asynchronous_sram_controller_handle &self,
						base::asynchronous_sram::ISRAMTimingProvider const &timing_provider);

	} // namespace asynchronous_sram
} // namespace base
