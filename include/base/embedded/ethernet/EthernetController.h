#pragma once
#include "ethernet_controller_handle.h"
#include <cstdint>
#include <memory>

namespace base
{
	namespace ethernet
	{
		///
		/// @brief 以太网控制器。
		///
		///
		class EthernetController
		{
		private:
			std::shared_ptr<base::ethernet::ethernet_controller_handle> _handle;

		public:
			EthernetController(uint32_t id)
			{
				_handle = base::ethernet::open(id);
			}

			///
			/// @brief 获取以太网控制器的 ID.
			///
			/// @return
			///
			uint32_t ID() const
			{
				return base::ethernet::id(*_handle);
			}

			///
			/// @brief 初始化以太网控制器。
			///
			/// @param type
			/// @param phy_address
			/// @param mac
			///
			void Initialize(base::ethernet::InterfaceType type,
							uint32_t phy_address,
							base::Mac const &mac) const
			{
				base::ethernet::initialize(*_handle,
										   type,
										   phy_address,
										   mac);
			}

			///
			/// @brief 获取以太网控制器所使用的 MAC 地址。
			///
			/// @return
			///
			base::Mac Mac() const
			{
				return base::ethernet::mac(*_handle);
			}

			/* #region 控制 PHY */

			///
			/// @brief 读取 PHY 的寄存器。
			///
			/// @param reg_index
			/// @return
			///
			uint32_t ReadPhyRegister(uint32_t reg_index) const
			{
				return base::ethernet::read_phy_register(*_handle, reg_index);
			}

			///
			/// @brief 写 PHY 的寄存器。
			///
			/// @param reg_index
			/// @param value
			///
			void WritePhyRegister(uint32_t reg_index, uint32_t value) const
			{
				base::ethernet::write_phy_register(*_handle, reg_index, value);
			}

			/* #endregion */

			///
			/// @brief 启动以太网控制器。
			///
			/// @note 通过读写 PHY 寄存器，控制 PHY 的初始化，等到 PHY 与远程连接后，读取出
			/// 使用的双工模式和连接速率，用来启动以太网控制器。因为以太网控制器不支持自动从 PHY
			/// 中获取这些信息。
			///
			/// @param duplex_mode 双工模式。
			/// @param speed 连接速率。
			///
			void Start(base::ethernet::DuplexMode duplex_mode,
					   base::unit::Mbps const &speed) const
			{
				base::ethernet::start(*_handle, duplex_mode, speed);
			}

			/* #region 收发数据 */

			///
			/// @brief 发送数据。
			///
			/// @param span
			///
			void Send(base::ReadOnlySpan const &span) const
			{
				base::ethernet::send(*_handle, span);
			}

			///
			/// @brief 发送数据。
			///
			/// @param spans 多个内存段中的数据合起来组成一个以太网帧。
			///
			void Send(std::vector<base::ReadOnlySpan> const &spans) const
			{
				base::ethernet::send(*_handle, spans);
			}

			///
			/// @brief 接收数据。
			///
			/// @return
			///
			base::ReadOnlySpan Receive() const
			{
				return base::ethernet::receive(*_handle);
			}

			/* #endregion */

			///
			/// @brief 通过 PHY 的复位引脚复位 PHY.
			///
			///
			void HardwareResetPhy()
			{
				base::ethernet::hardware_reset_phy(*_handle);
			}
		};

	} // namespace ethernet
} // namespace base
