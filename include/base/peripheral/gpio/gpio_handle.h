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

		///
		/// @brief 打开 GPIO 引脚。
		///
		/// @note 打开后即占用该引脚，无法再次打开，除非让 gpio_pin_handle 析构。
		///
		/// @param port
		/// @param pin
		/// @return base::gpio::sp_gpio_pin_handle
		///
		base::gpio::sp_gpio_pin_handle open(base::gpio::PortEnum port, uint32_t pin);

		/* #region 初始化函数 */

		///
		/// @brief 初始化为输入模式。
		///
		/// @param h
		/// @param pull_mode
		/// @param trigger_edge
		///
		void initialize_as_input_mode(base::gpio::sp_gpio_pin_handle const &h,
									  base::gpio::PullMode pull_mode,
									  base::gpio::TriggerEdge trigger_edge);

		///
		/// @brief 初始化为输出模式。
		///
		/// @param h
		/// @param pull_mode
		/// @param drive_mode
		///
		void initialize_as_output_mode(base::gpio::sp_gpio_pin_handle const &h,
									   base::gpio::PullMode pull_mode,
									   base::gpio::DriveMode drive_mode);

		///
		/// @brief 初始化为复用功能模式。
		///
		/// @param h
		/// @param af
		/// @param pull_mode
		/// @param drive_mode
		///
		void initialize_as_alternate_function_mode(base::gpio::sp_gpio_pin_handle const &h,
												   base::gpio::AlternateFunction af,
												   base::gpio::PullMode pull_mode,
												   base::gpio::DriveMode drive_mode);

		/* #endregion */

		///
		/// @brief 获取引脚名称。
		///
		/// @param h
		/// @return std::string
		///
		std::string pin_name(base::gpio::sp_gpio_pin_handle const &h);

		/* #region 读写引脚电平 */

		///
		/// @brief 读引脚电平。
		///
		/// @param h
		/// @return true
		/// @return false
		///
		bool read_pin(base::gpio::sp_gpio_pin_handle const &h);

		///
		/// @brief 写引脚电平。
		///
		/// @param h
		/// @param value
		///
		void write_pin(base::gpio::sp_gpio_pin_handle const &h, bool value);

		///
		/// @brief 翻转引脚电平。
		///
		/// @param h
		///
		void toggle_pin(base::gpio::sp_gpio_pin_handle const &h);

		/* #endregion */

		/* #region 中断回调 */

		///
		/// @brief 注册中断回调函数。
		///
		/// @param h
		/// @param callback_func
		///
		void register_interrupt_callback(base::gpio::sp_gpio_pin_handle const &h,
										 std::function<void()> const &callback_func);

		///
		/// @brief 取消注册中断回调函数。
		///
		/// @param h
		///
		void unregister_interrupt_callback(base::gpio::sp_gpio_pin_handle const &h);

		/* #endregion */

	} // namespace gpio
} // namespace base
