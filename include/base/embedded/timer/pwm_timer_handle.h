#pragma once
#include <cstdint>
#include <memory>

namespace base
{
	namespace pwm_timer
	{
		class pwm_timer_handle;

		std::shared_ptr<base::pwm_timer::pwm_timer_handle> open(uint32_t id);

	} // namespace pwm_timer
} // namespace base
