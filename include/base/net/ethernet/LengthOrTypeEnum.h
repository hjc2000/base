#pragma once
#include "base/string/ToHexString.h"
#include <cstdint>
#include <iostream>
#include <string>

namespace base::ethernet
{
	///
	/// @brief 提供以太网中一些上层协议的类型长度字段。
	///
	enum class LengthOrTypeEnum : uint16_t
	{
		///
		/// @brief IP 协议的类型长度字段。
		///
		IP = 0x0800,

		///
		/// @brief ARP 协议的类型长度字段。
		///
		ARP = 0x0806,

		///
		/// @brief VLAN 标签的类型长度字段。
		///
		/// @note VLAN 标签也叫 802.1Q 标签。
		///
		VlanTag = 0x8100,

		///
		/// @brief PROFINET 帧。
		///
		Profinet = 0x8892,

		///
		/// @brief MRP.
		///
		MRP = 0x88E3,

		///
		/// @brief EtherCAT.
		///
		EtherCAT = 0x88A4,

		///
		/// @brief LLDP.
		///
		LLDP = 0x88CC,
	};

} // namespace base::ethernet

namespace base
{
	inline std::string to_string(base::ethernet::LengthOrTypeEnum value)
	{
		std::string ret;

		switch (value)
		{
		case base::ethernet::LengthOrTypeEnum::IP:
			{
				ret = "IP";
				break;
			}
		case base::ethernet::LengthOrTypeEnum::ARP:
			{
				ret = "ARP";
				break;
			}
		case base::ethernet::LengthOrTypeEnum::VlanTag:
			{
				ret = "VlanTag";
				break;
			}
		case base::ethernet::LengthOrTypeEnum::Profinet:
			{
				ret = "Profinet";
				break;
			}
		case base::ethernet::LengthOrTypeEnum::MRP:
			{
				ret = "MRP";
				break;
			}
		case base::ethernet::LengthOrTypeEnum::EtherCAT:
			{
				ret = "EtherCAT";
				break;
			}
		case base::ethernet::LengthOrTypeEnum::LLDP:
			{
				ret = "LLDP";
				break;
			}
		default:
			{
				ret = "未知";
				break;
			}
		}

		ret += ": " + base::ToHexString(static_cast<uint16_t>(value));
		ret += " (十进制: " + std::to_string(static_cast<uint16_t>(value)) + ")";
		return ret;
	}

} // namespace base

///
/// @brief 将 base::ethernet::LengthOrTypeEnum 转换为字符串输出到输出流。
///
/// @param os
/// @param length_type
///
/// @return
///
inline std::ostream &operator<<(std::ostream &os, base::ethernet::LengthOrTypeEnum length_type)
{
	os << base::to_string(length_type);
	return os;
}
