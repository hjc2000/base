#pragma once
#include <functional>
#include <memory>
#include <string>

namespace base
{
	namespace gpio
	{
		/* #region 参数 */

		///
		/// @brief 引脚方向
		///
		enum class Direction
		{
			///
			/// @brief 输入
			///
			Input,

			///
			/// @brief 输出
			///
			Output,

			///
			/// @brief 双向
			///
			TwoWay,

			///
			/// @brief 高阻态。
			///
			HighResistanceState,
		};

		///
		/// @brief 引脚工作模式。
		///
		enum class WorkMode
		{
			///
			/// @brief 通用输入输出功能。
			///
			Gpio,

			///
			/// @brief 事件功能。
			///
			Event,

			///
			/// @brief 模拟量功能。
			///
			Analog,

			///
			/// @brief 复用功能。
			///
			AlternateFunction,
		};

		///
		/// @brief 触发边沿。
		///
		enum class TriggerEdge
		{
			///
			/// @brief 禁用中断
			///
			Disable,

			///
			/// @brief 上升沿
			///
			RisingEdge,

			///
			/// @brief 下降沿
			///
			FallingEdge,

			///
			/// @brief 双边沿
			///
			BothEdge,
		};

		///
		/// @brief 引脚上下拉模式。
		///
		enum class PullMode
		{
			///
			/// @brief 不拉
			///
			NoPull,

			///
			/// @brief 上拉
			///
			PullUp,

			///
			/// @brief 下拉
			///
			PullDown,
		};

		///
		/// @brief 引脚驱动模式。
		/// @note 引脚方向为输出时才有效。
		///
		enum class DriveMode
		{
			PushPull,
			OpenDrain,
		};

		///
		/// @brief 引脚复用功能枚举。
		///
		///
		enum class AlternateFunction
		{
			UART_RX,
			UART_TX,
		};

		/* #endregion */

		class gpio_pin_handle;
		using sp_gpio_pin_handle = std::shared_ptr<base::gpio::gpio_pin_handle>;

		/* #region 打开函数 */

		sp_gpio_pin_handle open_as_input_mode(base::gpio::PullMode pull_mode,
											  base::gpio::TriggerEdge trigger_edge);

		sp_gpio_pin_handle open_as_output_mode(base::gpio::PullMode pull_mode,
											   base::gpio::DriveMode drive_mode);

		sp_gpio_pin_handle open_as_alternate_function_mode(base::gpio::AlternateFunction af,
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
