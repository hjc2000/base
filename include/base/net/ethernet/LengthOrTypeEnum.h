#pragma once
#include <base/define.h>
#include <cstdint>
#include <iostream>
#include <string>

namespace base
{
	namespace ethernet
	{
		/**
		 * @brief 提供以太网中一些上层协议的类型长度字段。
		 *
		 */
		enum class LengthOrTypeEnum : uint16_t
		{
			/**
			 * @brief IP 协议的类型长度字段。
			 *
			 */
			IP = 0x0800,

			/**
			 * @brief ARP 协议的类型长度字段。
			 *
			 */
			ARP = 0x0806,

			/**
			 * @brief VLAN 标签的类型长度字段。
			 *
			 * @note VLAN 标签也叫 802.1Q 标签。
			 */
			VlanTag = 0x8100,

			/**
			 * @brief PROFINET 帧。
			 *
			 */
			Profinet = 0x8892,

			/**
			 * @brief MRP.
			 *
			 */
			MRP = 0x88E3,

			/**
			 * @brief EtherCAT.
			 *
			 */
			EtherCAT = 0x88A4,

			/**
			 * @brief LLDP.
			 *
			 */
			LLDP = 0x88CC,
		};
	} // namespace ethernet
} // namespace base

namespace std
{
	/**
	 * @brief 将 base::ethernet::LengthOrTypeEnum 转换为字符串。
	 *
	 * @param value
	 * @return std::string
	 */
	std::string to_string(base::ethernet::LengthOrTypeEnum value);
} // namespace std

/**
 * @brief 将 base::ethernet::LengthOrTypeEnum 转换为字符串输出到输出流。
 *
 * @param os
 * @param length_type
 * @return std::ostream&
 */
std::ostream &operator<<(std::ostream &os, base::ethernet::LengthOrTypeEnum length_type);
