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
			std::shared_ptr<base::gpio::gpio_pin_handle> _handle{};

		public:
			GpioPin(base::gpio::PortEnum port, uint32_t pin)
			{
				_handle = base::gpio::open(port, pin);
			}

			GpioPin(uint32_t pin_id)
			{
				_handle = base::gpio::open(pin_id);
			}

			///
			/// @brief 获取被包装的句柄。
			///
			/// @return
			///
			std::shared_ptr<base::gpio::gpio_pin_handle> const &Handle() const
			{
				return _handle;
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
				base::gpio::initialize_as_input_mode(*_handle, pull_mode, trigger_edge);
			}

			///
			/// @brief 初始化为输入模式。
			///
			/// @note 简单地初始化为输入模式。不关心上下拉。
			/// @note 不要使能中断。
			/// @note 只要保证能读取引脚的电平就行。
			///
			void InitializeAsInputMode()
			{
				base::gpio::initialize_as_input_mode(*_handle);
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
				base::gpio::initialize_as_output_mode(*_handle,
													  pull_mode,
													  drive_mode);
			}

			///
			/// @brief 初始化为输出模式。
			///
			/// @note 简单地配置为输出模式。不关心是上拉下拉，驱动方式是什么。反正只要能输出
			/// 高低电平就行。
			///
			void InitializeAsOutputMode()
			{
				base::gpio::initialize_as_output_mode(*_handle);
			}

			///
			/// @brief 初始化为复用功能模式。
			///
			/// @param alternate_function_id 复用功能的 ID.
			/// @param pull_mode
			/// @param drive_mode
			///
			void InitializeAsAlternateFunctionMode(uint32_t alternate_function_id,
												   base::gpio::PullMode pull_mode,
												   base::gpio::DriveMode drive_mode)
			{
				base::gpio::initialize_as_alternate_function_mode(*_handle,
																  alternate_function_id,
																  pull_mode,
																  drive_mode);
			}

			/* #endregion */

			/* #region 引脚信息 */

			///
			/// @brief GPIO 引脚名称。
			///
			/// @return std::string
			///
			std::string Name() const
			{
				return base::gpio::pin_name(*_handle);
			}

			///
			/// @brief 端口号。
			///
			/// @return
			///
			base::gpio::PortEnum Port() const
			{
				return base::gpio::port(*_handle);
			}

			///
			/// @brief 引脚号。
			///
			/// @return
			///
			uint32_t Pin() const
			{
				return base::gpio::pin(*_handle);
			}

			///
			/// @brief 引脚 ID.
			///
			/// @return
			///
			uint32_t PinId() const
			{
				return base::gpio::pin_id(*_handle);
			}

			/* #endregion */

			/* #region 读写引脚电平 */

			///
			/// @brief 读取引脚电平。
			///
			/// @return true
			/// @return false
			///
			bool ReadPin() const
			{
				return base::gpio::read_pin(*_handle);
			}

			///
			/// @brief 写引脚电平。
			///
			/// @param value
			///
			void WritePin(bool value)
			{
				base::gpio::write_pin(*_handle, value);
			}

			///
			/// @brief 翻转引脚电平。
			///
			///
			void TogglePin()
			{
				base::gpio::toggle_pin(*_handle);
			}

			/* #endregion */

			/* #region 中断回调 */

			///
			/// @brief 注册中断回调函数。
			///
			/// @param priority 中断优先级。
			/// @param callback_func 回调函数。
			///
			void RegisterInterruptCallback(int32_t priority, std::function<void()> const &callback_func)
			{
				base::gpio::register_interrupt_callback(*_handle, priority, callback_func);
			}

			///
			/// @brief 注册中断回调函数。
			///
			/// @param h
			/// @param callback_func
			///
			void RegisterInterruptCallback(std::function<void()> const &callback_func)
			{
				base::gpio::register_interrupt_callback(*_handle, callback_func);
			}

			///
			/// @brief 取消注册中断回调函数。
			///
			/// @param h
			///
			void UnregisterInterruptCallback()
			{
				base::gpio::unregister_interrupt_callback(*_handle);
			}

			/* #endregion */
		};

	} // namespace gpio
} // namespace base
