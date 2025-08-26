#pragma once
#include "input_capture_timer_handle.h"
#include <memory>

namespace base
{
	namespace input_capture_timer
	{
		class InputCaptureTimer
		{
		private:
			std::shared_ptr<base::input_capture_timer::input_capture_timer_handle> _handle;

		public:
		};

	} // namespace input_capture_timer
} // namespace base
