#include "LengthOrTypeEnum.h"
#include <base/string/ToHexString.h>

std::string base::ToString(base::ethernet::LengthOrTypeEnum value)
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

std::ostream &operator<<(std::ostream &os, base::ethernet::LengthOrTypeEnum length_type)
{
	os << base::ToString(length_type);
	return os;
}
