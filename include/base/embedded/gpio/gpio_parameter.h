#pragma once
#include <cstdint>
#include <string>

namespace base
{
	namespace gpio
	{
		///
		/// @brief GPIO 端口枚举。
		///
		///
		enum class PortEnum
		{
			PortA,
			PortB,
			PortC,
			PortD,
			PortE,
			PortF,
			PortG,
			PortH,
			PortI,
			PortJ,
			PortK,
			PortL,
			PortM,
			PortN,
			PortO,
			PortP,
		};

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
			UART1,
			UART2,
			UART3,

			SPI1,
			SPI2,
			SPI3,

			SDRAM1,

			NAND_FLASH1,

			TIMER1,
			TIMER2,
			TIMER3,
		};

	} // namespace gpio

	constexpr std::string to_string(base::gpio::PortEnum port)
	{
		switch (port)
		{
		case base::gpio::PortEnum::PortA:
			{
				return "PA";
			}
		case base::gpio::PortEnum::PortB:
			{
				return "PB";
			}
		case base::gpio::PortEnum::PortC:
			{
				return "PC";
			}
		case base::gpio::PortEnum::PortD:
			{
				return "PD";
			}
		case base::gpio::PortEnum::PortE:
			{
				return "PE";
			}
		case base::gpio::PortEnum::PortF:
			{
				return "PF";
			}
		case base::gpio::PortEnum::PortG:
			{
				return "PG";
			}
		case base::gpio::PortEnum::PortH:
			{
				return "PH";
			}
		case base::gpio::PortEnum::PortI:
			{
				return "PI";
			}
		case base::gpio::PortEnum::PortJ:
			{
				return "PJ";
			}
		case base::gpio::PortEnum::PortK:
			{
				return "PK";
			}
		case base::gpio::PortEnum::PortL:
			{
				return "PL";
			}
		case base::gpio::PortEnum::PortM:
			{
				return "PM";
			}
		case base::gpio::PortEnum::PortN:
			{
				return "PN";
			}
		case base::gpio::PortEnum::PortO:
			{
				return "PO";
			}
		case base::gpio::PortEnum::PortP:
			{
				return "PP";
			}
		default:
			{
				return "未知端口";
			}
		}
	}

	inline std::string PinName(base::gpio::PortEnum port, uint32_t pin)
	{
		return base::to_string(port) + std::to_string(pin);
	}

} // namespace base
