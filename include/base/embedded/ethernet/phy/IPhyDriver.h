#pragma once
#include "base/embedded/ethernet/EthernetController.h"
#include "base/embedded/ethernet/parameter.h"
#include "base/string/define.h"
#include "base/task/delay.h"
#include "base/unit/Mbps.h"

namespace base
{
	namespace ethernet
	{
		class IPhyDriver
		{
		public:
			///
			/// @brief PHY 驱动需要绑定一个以太网控制器才能控制 PHY 芯片。
			/// 这里用来获取绑定的以太网控制器。
			///
			/// @return
			///
			virtual base::ethernet::EthernetController &EthernetController() = 0;

			///
			/// @brief 获取此网口的双工模式。
			/// @return
			///
			virtual base::ethernet::DuplexMode DuplexMode() = 0;

			///
			/// @brief 获取此网口的速度。
			/// @return
			///
			virtual base::unit::Mbps Speed() = 0;

			///
			/// @brief 软件复位 PHY.
			///
			void SoftwareReset()
			{
				/* BCR 的 bit15 用来软件复位。写入 1 立刻进行软件复位。
				 * 复位过程中，bit15 会保持为 1，复位完成后自动清 0. 所以可以通过检查自动清 0
				 * 来判断复位结束。
				 */
				uint32_t const mask = 0b1 << 15;
				WriteRegister(0, mask);

				int delay_times = 0;
				while (true)
				{
					uint32_t bcr = ReadRegister(0);
					uint32_t value = bcr & mask;
					if (!value)
					{
						// 自动清 0，复位完成。
						return;
					}

					base::task::Delay(std::chrono::milliseconds{10});
					delay_times++;
					if (delay_times > 1000)
					{
						throw std::runtime_error{"软件复位超时。"};
					}
				}
			}

			///
			/// @brief 通过 PHY 的复位引脚将 PHY 复位。
			///
			void HardwareReset()
			{
				EthernetController().HardwareResetPhy();
			}

			/* #region 自动协商 */

			///
			/// @brief 检查本网口是否支持自动协商。
			/// @return 支持则返回 true，不支持则返回 false.
			///
			bool SupportAutoNegotiation()
			{
				/* BSR bit3 指示是否支持自动协商。
				 *		0：不支持自动协商。
				 *		1：支持自动协商。
				 */
				uint32_t bcr = ReadRegister(1);
				uint32_t mask = 0b1 << 3;
				uint32_t value = (bcr & mask) >> 3;
				return value;
			}

			///
			/// @brief 使能自动协商。
			/// @note 会先判断 PHY 是否支持自动协商，不支持自动协商会抛出异常。
			/// @note 使能自动协商后会等待 PHY 自动协商完成。等待超时后会抛出异常。
			///
			void EnableAutoNegotiation()
			{
				if (!SupportAutoNegotiation())
				{
					throw std::runtime_error{CODE_POS_STR + "本网口不支持自动协商。"};
				}

				/* 要先检查 BSR 看是否支持自动协商，支持才开启。
				 * 开启后要检查 BSR 寄存器，等待直到自动协商完成或超时。
				 */
				uint32_t bcr = ReadRegister(0);
				bcr |= 0x1000U;
				WriteRegister(0, bcr);

				int delay_times = 0;
				while (true)
				{
					if (AutoNegotiationCompleted())
					{
						return;
					}

					base::task::Delay(std::chrono::milliseconds{10});
					delay_times++;

					// 根据 IEEE 的规定，自动协商不应该超过 500ms，这里放宽松一点。
					if (delay_times > 1000)
					{
						throw std::runtime_error{CODE_POS_STR + "等待自动协商完成超时"};
					}
				}
			}

			///
			/// @brief 自动协商完成。
			/// @return
			///
			bool AutoNegotiationCompleted()
			{
				/* BSR bit5 指示自动协商是否完成。
				 *		0：自动协商未完成。
				 *		1：自动协商完成。
				 */
				uint32_t bcr = ReadRegister(1);
				uint32_t mask = 0b1 << 5;
				uint32_t value = (bcr & mask) >> 5;
				return value;
			}

			/* #endregion */

			void EnablePowerDownMode()
			{
				uint32_t bcr = ReadRegister(0);
				bcr |= 0x0800U;
				WriteRegister(0, bcr);
			}

			void DisablePowerDownMode()
			{
				uint32_t bcr = ReadRegister(0);
				bcr &= ~0x0800U;
				WriteRegister(0, bcr);
			}

			void EnableLoopbackMode()
			{
				uint32_t register_value = ReadRegister(0);
				register_value |= 0x4000U;
				WriteRegister(0, register_value);
			}

			void DisableLoopbackMode()
			{
				uint32_t register_value = ReadRegister(0);
				register_value &= ~0x4000U;
				WriteRegister(0, register_value);
			}

			///
			/// @brief 网线当前处于链接状态。
			/// @return
			///
			bool IsLinked()
			{
				uint32_t regval = ReadRegister(1);
				bool is_linked = regval & 0x0004U;
				return is_linked;
			}

			///
			/// @brief 读 PHY 的寄存器
			/// @param register_index 寄存器索引。
			/// @return
			///
			uint32_t ReadRegister(uint32_t register_index)
			{
				return EthernetController().ReadPhyRegister(register_index);
			}

			///
			/// @brief 写 PHY 的寄存器。
			/// @param register_index 寄存器索引。
			/// @param value
			///
			void WriteRegister(uint32_t register_index, uint32_t value)
			{
				EthernetController().WritePhyRegister(register_index, value);
			}
		};

	} // namespace ethernet
} // namespace base
