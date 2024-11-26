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
    case base::ethernet::LengthTypeEnum::LLDP:
        {
            return "LLDP " + base::ToHexString(static_cast<uint16_t>(value));
        }
    default:
        {
            return "暂不支持将此枚举值转为字符串 " + base::ToHexString(static_cast<uint16_t>(value));
        }
    }
}

std::ostream &operator<<(std::ostream &os, base::ethernet::LengthTypeEnum value)
{
    os << base::ToString(value);
    return os;
}
