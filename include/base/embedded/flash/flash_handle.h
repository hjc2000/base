#pragma once
#include <cstdint>
#include <memory>

namespace base
{
	namespace flash
	{
		class flash_handle;

		std::shared_ptr<flash_handle> open(uint32_t id);

		void initialize(base::flash::flash_handle &self);

	} // namespace flash
} // namespace base
