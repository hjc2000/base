#include "LengthTypeEnum.h"

std::string base::ToString(base::ethernet::LengthTypeEnum value)
{
    switch (value)
    {
    case base::ethernet::LengthTypeEnum::IP:
        {
            return "IP";
        }
    case base::ethernet::LengthTypeEnum::ARP:
        {
            return "ARP";
        }
    case base::ethernet::LengthTypeEnum::VlanTag:
        {
            return "VlanTag";
        }
    case base::ethernet::LengthTypeEnum::Profinet:
        {
            return "Profinet";
        }
    case base::ethernet::LengthTypeEnum::MRP:
        {
            return "MRP";
        }
    case base::ethernet::LengthTypeEnum::LLDP:
        {
            return "LLDP";
        }
    default:
        {
            return "暂不支持将此枚举值转为字符串";
        }
    }
}

std::ostream &operator<<(std::ostream &os, base::ethernet::LengthTypeEnum value)
{
    os << base::ToString(value);
    return os;
}
