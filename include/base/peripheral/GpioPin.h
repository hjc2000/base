#pragma once
#include "gpio_handle.h"
#include <cstdint>
#include <string>

namespace base
{
	namespace gpio
	{
		///
		/// @brief 包装 GPIO 句柄，提供面向对象风格的体验。
		///
		///
		class GpioPin
		{
		private:
			base::gpio::PortEnum _port{};
			uint32_t _pin{};
			base::gpio::sp_gpio_pin_handle _handle{};

		public:
			///
			/// @brief 构造时会打开 GPIO 引脚。
			///
			/// @param port
			/// @param pin
			///
			GpioPin(base::gpio::PortEnum port, uint32_t pin)
				: _port(port),
				  _pin(pin)
			{
				_handle = base::gpio::open(_port, _pin);
			}

			/* #region 初始化函数 */

			///
			/// @brief 初始化为输入模式。
			///
			/// @param pull_mode
			/// @param trigger_edge
			///
			void InitializeAsInputMode(base::gpio::PullMode pull_mode,
									   base::gpio::TriggerEdge trigger_edge)
			{
				base::gpio::initialize_as_input_mode(_handle, pull_mode, trigger_edge);
			}

			///
			/// @brief 初始化为输出模式。
			///
			/// @param pull_mode
			/// @param drive_mode
			///
			void InitializeAsOutputMode(base::gpio::PullMode pull_mode,
										base::gpio::DriveMode drive_mode)
			{
				base::gpio::initialize_as_output_mode(_handle,
													  pull_mode,
													  drive_mode);
			}

			///
			/// @brief 初始化为复用功能模式。
			///
			/// @param af
			/// @param pull_mode
			/// @param drive_mode
			///
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

			///
			/// @brief GPIO 引脚名称。
			///
			/// @return std::string
			///
			std::string Name() const
			{
				return base::gpio::pin_name(_handle);
			}

			/* #region 读写引脚电平 */

			///
			/// @brief 读取引脚电平。
			///
			/// @return true
			/// @return false
			///
			bool ReadPin() const
			{
				return base::gpio::read_pin(_handle);
			}

			///
			/// @brief 写引脚电平。
			///
			/// @param value
			///
			void WritePin(bool value)
			{
				base::gpio::write_pin(_handle, value);
			}

			///
			/// @brief 翻转引脚电平。
			///
			/// @param h
			///
			void TogglePin(base::gpio::sp_gpio_pin_handle const &h)
			{
				base::gpio::toggle_pin(_handle);
			}

			/* #endregion */

			/* #region 中断回调 */

			///
			/// @brief 注册中断回调函数。
			///
			/// @param h
			/// @param callback_func
			///
			void RegisterInterruptCallback(std::function<void()> const &callback_func)
			{
				base::gpio::register_interrupt_callback(_handle, callback_func);
			}

			///
			/// @brief 取消注册中断回调函数。
			///
			/// @param h
			///
			void UnregisterInterruptCallback()
			{
				base::gpio::unregister_interrupt_callback(_handle);
			}

			/* #endregion */
		};

	} // namespace gpio
} // namespace base
