#pragma once
#include "base/define.h"
#include "base/peripheral/led/parameter.h"

namespace base
{
	namespace led
	{
		class led_handle;

		void turn_on(base::led::led_handle &h);
		void turn_off(base::led::led_handle &h);
		void toggle(base::led::led_handle &h);

		base::led::State state(base::led::led_handle &h);

		///
		/// @brief 设置 LED 灯的状态。
		///
		/// @param h
		/// @param value
		///
		IMPLEMENTED
		void set_state(base::led::led_handle &h, base::led::State value);

	} // namespace led
} // namespace base
