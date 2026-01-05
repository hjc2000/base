#pragma once
#include "base/net/Mac.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/unit/Mbps.h"
#include "parameter.h"
#include <cstdint>
#include <memory>
#include <vector>

namespace base
{
	namespace ethernet
	{
		class ethernet_controller_handle;

		///
		/// @brief 根据以太网控制器的 ID 打开以太网控制器。
		///
		/// @param id 以太网控制器的 ID.
		/// @return
		///
		std::shared_ptr<base::ethernet::ethernet_controller_handle> open(uint32_t id);

		///
		/// @brief 获取以太网控制器的 ID.
		///
		/// @param h
		/// @return
		///
		uint32_t id(base::ethernet::ethernet_controller_handle &h);

		///
		/// @brief 初始化以太网控制器。
		///
		/// @param h
		/// @param type
		/// @param phy_address
		/// @param mac
		///
		void initialize(base::ethernet::ethernet_controller_handle &h,
						base::ethernet::InterfaceType type,
						uint32_t phy_address,
						base::Mac const &mac);

		///
		/// @brief 获取以太网控制器所使用的 MAC 地址。
		///
		/// @param h
		/// @return
		///
		base::Mac mac(base::ethernet::ethernet_controller_handle &h);

		/* #region 控制 PHY */

		///
		/// @brief 读取 PHY 的寄存器。
		///
		/// @param h
		/// @param reg_index
		/// @return
		///
		uint32_t read_phy_register(base::ethernet::ethernet_controller_handle &h,
								   uint32_t reg_index);

		///
		/// @brief 写 PHY 的寄存器。
		///
		/// @param h
		/// @param reg_index
		/// @param value
		///
		void write_phy_register(base::ethernet::ethernet_controller_handle &h,
								uint32_t reg_index,
								uint32_t value);

		/* #endregion */

		///
		/// @brief 启动以太网控制器。
		///
		/// @note 通过读写 PHY 寄存器，控制 PHY 的初始化，等到 PHY 与远程连接后，读取出
		/// 使用的双工模式和连接速率，用来启动以太网控制器。因为以太网控制器不支持自动从 PHY
		/// 中获取这些信息。
		///
		/// @param h
		/// @param duplex_mode 双工模式。
		/// @param speed 连接速率。
		///
		void start(base::ethernet::ethernet_controller_handle &h,
				   base::ethernet::DuplexMode duplex_mode,
				   base::unit::Mbps const &speed);

		/* #region 收发数据 */

		///
		/// @brief 发送数据。
		///
		/// @param h
		/// @param span
		///
		void send(base::ethernet::ethernet_controller_handle &h,
				  base::ReadOnlySpan const &span);

		///
		/// @brief 发送数据。
		///
		/// @param h
		/// @param spans 多个内存段中的数据合起来组成一个以太网帧。
		///
		void send(base::ethernet::ethernet_controller_handle &h,
				  std::vector<base::ReadOnlySpan> const &spans);

		///
		/// @brief 接收数据。
		///
		/// @param h
		/// @return
		///
		base::ReadOnlySpan receive(base::ethernet::ethernet_controller_handle &h);

		/* #endregion */

		///
		/// @brief 底层初始化回调。
		///
		/// @note BSP 层负责实现。
		/// @note 初始化例如 GPIO 引脚等。
		///
		/// @param id
		///
		void msp_initialize_callback(uint32_t id);

		///
		/// @brief 通过 PHY 的复位引脚复位 PHY.
		///
		/// @note BSP 层负责实现。
		///
		/// @param h
		///
		void hardware_reset_phy(base::ethernet::ethernet_controller_handle &h);

	} // namespace ethernet
} // namespace base
