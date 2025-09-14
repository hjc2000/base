#pragma once
#include "base/embedded/ethernet/EthernetController.h"
#include "base/embedded/ethernet/parameter.h"
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
			void SoftwareReset();

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
			bool SupportAutoNegotiation();

			///
			/// @brief 使能自动协商。
			/// @note 会先判断 PHY 是否支持自动协商，不支持自动协商会抛出异常。
			/// @note 使能自动协商后会等待 PHY 自动协商完成。等待超时后会抛出异常。
			///
			void EnableAutoNegotiation();

			///
			/// @brief 自动协商完成。
			/// @return
			///
			bool AutoNegotiationCompleted();
			/* #endregion */

			void EnablePowerDownMode();
			void DisablePowerDownMode();

			void EnableLoopbackMode();
			void DisableLoopbackMode();

			///
			/// @brief 网线当前处于链接状态。
			/// @return
			///
			bool IsLinked();

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
