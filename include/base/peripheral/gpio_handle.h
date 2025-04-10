#pragma once
#include "gpio_parameter.h"
#include <cstdint>
#include <functional>
#include <memory>
#include <string>

namespace base
{
	namespace gpio
	{
		class gpio_pin_handle;
		using sp_gpio_pin_handle = std::shared_ptr<base::gpio::gpio_pin_handle>;

		base::gpio::sp_gpio_pin_handle open(base::gpio::PortEnum port, uint32_t pin);

		/* #region 初始化函数 */

		void initialize_as_input_mode(base::gpio::sp_gpio_pin_handle const &h,
									  base::gpio::PullMode pull_mode,
									  base::gpio::TriggerEdge trigger_edge);

		void initialize_as_output_mode(base::gpio::sp_gpio_pin_handle const &h,
									   base::gpio::PullMode pull_mode,
									   base::gpio::DriveMode drive_mode);

		void initialize_as_alternate_function_mode(base::gpio::sp_gpio_pin_handle const &h,
												   base::gpio::AlternateFunction af,
												   base::gpio::PullMode pull_mode,
												   base::gpio::DriveMode drive_mode);

		/* #endregion */

		std::string pin_name(base::gpio::sp_gpio_pin_handle const &h);

		bool read_pin(base::gpio::sp_gpio_pin_handle const &h);
		void write_pin(base::gpio::sp_gpio_pin_handle const &h, bool value);
		void toggle_pin(base::gpio::sp_gpio_pin_handle const &h);

		///
		/// @brief 注册中断回调函数。
		///
		/// @param h
		/// @param callback_func
		///
		void register_interrupt_callback(base::gpio::sp_gpio_pin_handle const &h, std::function<void()> callback_func);

		///
		/// @brief 取消注册中断回调函数。
		///
		/// @param h
		///
		void unregister_interrupt_callback(base::gpio::sp_gpio_pin_handle const &h);

	} // namespace gpio
} // namespace base
