#include "IPAddress.h"
#include <stdexcept>

base::IPAddress::IPAddress()
{
    _type = IPAddressType::IPV4;
    _span = base::Span{_ip_address_buffer.Buffer(), 4};
}

base::IPAddress::IPAddress(IPAddressType type)
{
    _type = type;
    if (_type == IPAddressType::IPV4)
    {
        _span = base::Span{_ip_address_buffer.Buffer(), 4};
    }
    else
    {
        _span = base::Span{_ip_address_buffer.Buffer(), 16};
    }
}

base::IPAddress::IPAddress(std::endian endian, base::Array<uint8_t, 4> const &ip_address_buffer)
{
    _type = IPAddressType::IPV4;
    _span = base::Span{_ip_address_buffer.Buffer(), 4};

    _span.CopyFrom(0,
                   ip_address_buffer.Buffer(),
                   0,
                   ip_address_buffer.Count());

    // 用小端序存放 IPV4 地址
    if (endian != std::endian::little)
    {
        _span.Reverse();
    }
}

base::IPAddress::IPAddress(std::endian endian, base::Array<uint8_t, 16> const &ip_address_buffer)
{
    _type = IPAddressType::IPV6;
    _span = base::Span{_ip_address_buffer.Buffer(), 16};

    _span.CopyFrom(0,
                   ip_address_buffer.Buffer(),
                   0,
                   ip_address_buffer.Count());

    // 用小端序存放 IPV6 地址
    if (endian != std::endian::little)
    {
        _span.Reverse();
    }
}

base::IPAddress::IPAddress(IPAddress const &o)
{
    *this = o;
}

base::IPAddress &base::IPAddress::operator=(IPAddress const &o)
{
    _ip_address_buffer = o._ip_address_buffer;
    _span = base::Span{_ip_address_buffer.Buffer(), o._span.Size()};
    _type = _type;
    return *this;
}

uint8_t &base::IPAddress::operator[](int index)
{
    if (index < 0 || index >= _span.Size())
    {
        throw std::out_of_range{"索引超出范围"};
    }

    return _span[index];
}

uint8_t base::IPAddress::operator[](int index) const
{
    if (index < 0 || index >= _span.Size())
    {
        throw std::out_of_range{"索引超出范围"};
    }

    return _span[index];
}
