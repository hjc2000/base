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

		/* #region open */

		///
		/// @brief 打开 GPIO 引脚。
		///
		/// @note 打开后即占用该引脚，无法再次打开，除非让 gpio_pin_handle 析构。
		///
		/// @param port
		/// @param pin
		/// @return base::gpio::sp_gpio_pin_handle
		///
		std::shared_ptr<base::gpio::gpio_pin_handle> open(base::gpio::PortEnum port, uint32_t pin);

		///
		/// @brief 根据引脚 ID 打开引脚。
		///
		/// @param pin_id
		/// @return
		///
		std::shared_ptr<base::gpio::gpio_pin_handle> open(uint32_t pin_id);

		/* #endregion */

		/* #region 初始化函数 */

		///
		/// @brief 初始化为输入模式。
		///
		/// @param h
		/// @param pull_mode
		/// @param trigger_edge
		///
		void initialize_as_input_mode(base::gpio::gpio_pin_handle &h,
									  base::gpio::PullMode pull_mode,
									  base::gpio::TriggerEdge trigger_edge);

		///
		/// @brief 初始化为输入模式。
		///
		/// @note 简单地初始化为输入模式。不关心上下拉。
		/// @note 不要使能中断。
		/// @note 只要保证能读取引脚的电平就行。
		///
		/// @param h
		///
		void initialize_as_input_mode(base::gpio::gpio_pin_handle &h);

		///
		/// @brief 初始化为输出模式。
		///
		/// @param h
		/// @param pull_mode
		/// @param drive_mode
		///
		void initialize_as_output_mode(base::gpio::gpio_pin_handle &h,
									   base::gpio::PullMode pull_mode,
									   base::gpio::DriveMode drive_mode);

		///
		/// @brief 初始化为输出模式。
		///
		/// @note 简单地配置为输出模式。不关心是上拉下拉，驱动方式是什么。反正只要能输出
		/// 高低电平就行。
		///
		/// @param h
		///
		void initialize_as_output_mode(base::gpio::gpio_pin_handle &h);

		///
		/// @brief 初始化为复用功能模式。
		///
		/// @param h
		///
		/// @param alternate_function_id 复用功能的 ID.
		/// @param pull_mode
		/// @param drive_mode
		///
		void initialize_as_alternate_function_mode(base::gpio::gpio_pin_handle &h,
												   uint32_t alternate_function_id,
												   base::gpio::PullMode pull_mode,
												   base::gpio::DriveMode drive_mode);

		/* #endregion */

		/* #region 引脚信息 */

		///
		/// @brief 获取引脚名称。
		///
		/// @param h
		/// @return std::string
		///
		std::string pin_name(base::gpio::gpio_pin_handle &h);

		///
		/// @brief 端口号。
		///
		/// @param h
		/// @return
		///
		base::gpio::PortEnum port(base::gpio::gpio_pin_handle &h);

		///
		/// @brief 引脚号。
		///
		/// @param h
		/// @return
		///
		uint32_t pin(base::gpio::gpio_pin_handle &h);

		///
		/// @brief 引脚 ID.
		///
		/// @param h
		/// @return
		///
		uint32_t pin_id(base::gpio::gpio_pin_handle &h);

		/* #endregion */

		/* #region 读写引脚电平 */

		///
		/// @brief 读引脚电平。
		///
		/// @param h
		/// @return true
		/// @return false
		///
		bool read_pin(base::gpio::gpio_pin_handle &h);

		///
		/// @brief 写引脚电平。
		///
		/// @param h
		/// @param value
		///
		void write_pin(base::gpio::gpio_pin_handle &h, bool value);

		///
		/// @brief 翻转引脚电平。
		///
		/// @param h
		///
		void toggle_pin(base::gpio::gpio_pin_handle &h);

		/* #endregion */

		/* #region 中断回调 */

		///
		/// @brief 注册中断回调函数。
		///
		/// @param h
		/// @param priority 中断优先级。
		/// @param callback_func 回调函数。
		///
		void register_interrupt_callback(base::gpio::gpio_pin_handle &h,
										 int32_t priority,
										 std::function<void()> const &callback_func);

		///
		/// @brief 注册中断回调函数。
		///
		/// @param h
		/// @param callback_func
		///
		void register_interrupt_callback(base::gpio::gpio_pin_handle &h,
										 std::function<void()> const &callback_func);

		///
		/// @brief 取消注册中断回调函数。
		///
		/// @param h
		///
		void unregister_interrupt_callback(base::gpio::gpio_pin_handle &h);

		/* #endregion */

	} // namespace gpio
} // namespace base
