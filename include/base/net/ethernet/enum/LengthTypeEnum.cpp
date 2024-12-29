#include "LengthTypeEnum.h"
#include <base/string/ToHexString.h>

std::string base::ToString(base::ethernet::LengthTypeEnum value)
{
	std::string ret;
	switch (value)
	{
	case base::ethernet::LengthTypeEnum::IP:
		{
			ret = "IP";
			break;
		}
	case base::ethernet::LengthTypeEnum::ARP:
		{
			ret = "ARP";
			break;
		}
	case base::ethernet::LengthTypeEnum::VlanTag:
		{
			ret = "VlanTag";
			break;
		}
	case base::ethernet::LengthTypeEnum::Profinet:
		{
			ret = "Profinet";
			break;
		}
	case base::ethernet::LengthTypeEnum::MRP:
		{
			ret = "MRP";
			break;
		}
	case base::ethernet::LengthTypeEnum::EtherCAT:
		{
			ret = "EtherCAT";
			break;
		}
	case base::ethernet::LengthTypeEnum::LLDP:
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

std::ostream &operator<<(std::ostream &os, base::ethernet::LengthTypeEnum length_type)
{
	os << base::ToString(length_type);
	return os;
}
