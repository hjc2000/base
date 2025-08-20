#pragma once

#include <memory>

namespace base
{
	namespace asynchronous_sram
	{
		class asynchronous_sram_controller_handle;

		std::shared_ptr<base::asynchronous_sram::asynchronous_sram_controller_handle> open();

	} // namespace asynchronous_sram
} // namespace base
