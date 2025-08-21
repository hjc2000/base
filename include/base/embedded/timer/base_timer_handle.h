#pragma once
#include <cstdint>
#include <memory>

namespace base
{
	namespace base_timer
	{
		class base_timer_handle;

		std::shared_ptr<base::base_timer::base_timer_handle> open(uint32_t id);

		void initialize(base::base_timer::base_timer_handle &self);

	} // namespace base_timer
} // namespace base
