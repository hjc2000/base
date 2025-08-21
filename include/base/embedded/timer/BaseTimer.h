#pragma once
#include "base_timer_handle.h"
#include <cstdint>
#include <memory>

namespace base
{
	namespace base_timer
	{
		class BaseTimer
		{
		private:
			std::shared_ptr<base::base_timer::base_timer_handle> _handle;

		public:
			BaseTimer(uint32_t id)
			{
				_handle = base::base_timer::open(id);
			}
		};

	} // namespace base_timer
} // namespace base
