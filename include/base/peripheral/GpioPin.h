#pragma once
#include "gpio_handle.h"
#include <string>

namespace base
{
	namespace gpio
	{
		class GpioPin
		{
		private:
			base::gpio::sp_gpio_pin_handle _handle{};

		public:
			GpioPin(base::gpio::sp_gpio_pin_handle const &h)
				: _handle(h)
			{
			}

			std::string Name() const
			{
				return base::gpio::pin_name(_handle);
			}

			bool ReadPin() const
			{
				return base::gpio::read_pin(_handle);
			}

			void WritePin(bool value)
			{
				base::gpio::write_pin(_handle, value);
			}

			void TogglePin(base::gpio::sp_gpio_pin_handle const &h)
			{
				base::gpio::toggle_pin(_handle);
			}
		};

	} // namespace gpio
} // namespace base
