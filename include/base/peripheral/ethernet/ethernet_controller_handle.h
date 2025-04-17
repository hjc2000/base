#pragma once
#include "base/net/Mac.h"
#include "parameter.h"
#include <cstdint>
#include <memory>

namespace base
{
	namespace ethernet
	{
		class ethernet_controller_handle;

		/* #region open */

		///
		/// @brief 打开以太网控制器。
		///
		/// @note 如果只有一个以太网控制器，可以使用本函数打开。
		///
		/// @return
		///
		std::shared_ptr<base::ethernet::ethernet_controller_handle> open();

		///
		/// @brief 根据以太网控制器的 ID 打开以太网控制器。
		///
		/// @param id 以太网控制器的 ID.
		/// @return
		///
		std::shared_ptr<base::ethernet::ethernet_controller_handle> open(uint32_t id);

		/* #endregion */

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

	} // namespace ethernet
} // namespace base
