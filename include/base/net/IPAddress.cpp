#include "IPAddress.h"
#include <stdexcept>

base::IPAddress::IPAddress(std::endian endian, base::Array<uint8_t, 4> const &ip_address_buffer)
{
    _type = IPAddressType::IPV4;
    _ip_address_buffer.CopyFrom(0,
                                ip_address_buffer.Buffer(),
                                0,
                                4);

    // 用小端序存放 IPV4 地址
    if (endian != std::endian::little)
    {
        std::reverse(_ip_address_buffer.Buffer(),
                     _ip_address_buffer.Buffer() + 4);
    }
}

base::IPAddress::IPAddress(std::endian endian, base::Array<uint8_t, 16> const &ip_address_buffer)
{
    _type = IPAddressType::IPV6;
    _ip_address_buffer = ip_address_buffer;

    // 用小端序存放 IPV6 地址
    if (endian != std::endian::little)
    {
        _ip_address_buffer.Reverse();
    }
}

uint8_t &base::IPAddress::operator[](int index)
{
    if (index < 0)
    {
        throw std::out_of_range{"索引超出范围"};
    }

    if (_type == IPAddressType::IPV4)
    {
        if (index > 4)
        {
            throw std::out_of_range{"索引超出范围"};
        }
    }
    else
    {
        if (index > 16)
        {
            throw std::out_of_range{"索引超出范围"};
        }
    }

    return _ip_address_buffer[index];
}
