#pragma once
#include <cstdint>
#include <memory>

namespace base
{
	namespace input_capture_timer
	{
		class input_capture_timer_handle;

		std::shared_ptr<base::input_capture_timer::input_capture_timer_handle> open(uint32_t id);

		///
		/// @brief 输入捕获定时器的底层初始化回调。
		///
		/// @param id
		///
		void msp_initialize_callback(uint32_t id);

	} // namespace input_capture_timer
} // namespace base
