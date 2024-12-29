#include "LengthTypeEnum.h"
#include <base/string/ToHexString.h>

std::string base::ToString(base::ethernet::LengthTypeEnum value)
{
	switch (value)
	{
	case base::ethernet::LengthTypeEnum::IP:
		{
			return "IP " + base::ToHexString(static_cast<uint16_t>(value));
		}
	case base::ethernet::LengthTypeEnum::ARP:
		{
			return "ARP " + base::ToHexString(static_cast<uint16_t>(value));
		}
	case base::ethernet::LengthTypeEnum::VlanTag:
		{
			return "VlanTag " + base::ToHexString(static_cast<uint16_t>(value));
		}
	case base::ethernet::LengthTypeEnum::Profinet:
		{
			return "Profinet " + base::ToHexString(static_cast<uint16_t>(value));
		}
	case base::ethernet::LengthTypeEnum::MRP:
		{
			return "MRP " + base::ToHexString(static_cast<uint16_t>(value));
		}
	case base::ethernet::LengthTypeEnum::EtherCAT:
		{
			return "EtherCAT " + base::ToHexString(static_cast<uint16_t>(value));
		}
	case base::ethernet::LengthTypeEnum::LLDP:
		{
			return "LLDP " + base::ToHexString(static_cast<uint16_t>(value));
		}
	default:
		{
			return "未知 " + base::ToHexString(static_cast<uint16_t>(value));
		}
	}
}
