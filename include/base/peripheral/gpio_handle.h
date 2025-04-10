#pragma once
#include "gpio_parameter.h"
#include <functional>
#include <memory>
#include <string>

namespace base
{
	namespace gpio
	{
		class gpio_pin_handle;
		using sp_gpio_pin_handle = std::shared_ptr<base::gpio::gpio_pin_handle>;

		/* #region 打开函数 */

		sp_gpio_pin_handle open_as_input_mode(base::gpio::PortEnum port,
											  int pin,
											  base::gpio::PullMode pull_mode,
											  base::gpio::TriggerEdge trigger_edge);

		sp_gpio_pin_handle open_as_output_mode(base::gpio::PortEnum port,
											   int pin,
											   base::gpio::PullMode pull_mode,
											   base::gpio::DriveMode drive_mode);

		sp_gpio_pin_handle open_as_alternate_function_mode(base::gpio::PortEnum port,
														   int pin,
														   base::gpio::AlternateFunction af,
														   base::gpio::PullMode pull_mode,
														   base::gpio::DriveMode drive_mode);

		/* #endregion */

		std::string pin_name(sp_gpio_pin_handle const &h);

		bool read_pin(sp_gpio_pin_handle const &h);
		void write_pin(sp_gpio_pin_handle const &h, bool value);
		void toggle_pin(sp_gpio_pin_handle const &h);

		///
		/// @brief 注册中断回调函数。
		///
		/// @param h
		/// @param callback_func
		///
		void register_interrupt_callback(sp_gpio_pin_handle const &h, std::function<void()> callback_func);

		///
		/// @brief 取消注册中断回调函数。
		///
		/// @param h
		///
		void unregister_interrupt_callback(sp_gpio_pin_handle const &h);

	} // namespace gpio
} // namespace base
