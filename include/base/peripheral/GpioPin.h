#pragma once
#include "gpio_handle.h"
#include <cstdint>
#include <string>

namespace base
{
	namespace gpio
	{
		class GpioPin
		{
		private:
			base::gpio::PortEnum _port{};
			uint32_t _pin{};
			base::gpio::sp_gpio_pin_handle _handle{};

		public:
			GpioPin(base::gpio::PortEnum port, uint32_t pin)
				: _port(port),
				  _pin(pin)
			{
				_handle = base::gpio::open(_port, _pin);
			}

			/* #region 初始化函数 */

			void InitializeAsInputMode(base::gpio::PullMode pull_mode,
									   base::gpio::TriggerEdge trigger_edge)
			{
				base::gpio::initialize_as_input_mode(_handle, pull_mode, trigger_edge);
			}

			void InitializeAsOutputMode(base::gpio::PullMode pull_mode,
										base::gpio::DriveMode drive_mode)
			{
				base::gpio::initialize_as_output_mode(_handle,
													  pull_mode,
													  drive_mode);
			}

			void InitializeAsAlternateFunctionMode(base::gpio::AlternateFunction af,
												   base::gpio::PullMode pull_mode,
												   base::gpio::DriveMode drive_mode)
			{
				base::gpio::initialize_as_alternate_function_mode(_handle,
																  af,
																  pull_mode,
																  drive_mode);
			}

			/* #endregion */

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
