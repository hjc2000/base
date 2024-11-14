#include "IPAddress.h"
#include <base/string/ToHexString.h>
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

uint8_t const &base::IPAddress::operator[](int index) const
{
    if (index < 0 || index >= _span.Size())
    {
        throw std::out_of_range{"索引超出范围"};
    }

    return _span[index];
}

std::string base::IPAddress::ToString() const
{
    std::string ret;
    base::ToHexStringOption option;
    option.width = 2;
    option.with_0x_prefix = false;

    if (_type == IPAddressType::IPV4)
    {
        bool first_loop = true;
        for (uint8_t num : _span)
        {
            if (first_loop)
            {
                first_loop = false;
            }
            else
            {
                ret = '.' + ret;
            }

            ret = std::to_string(num) + ret;
        }
    }
    else
    {
        int loop_times = 0;
        for (uint8_t num : _span)
        {
            if (loop_times > 0 && loop_times % 2 == 0)
            {
                ret = ':' + ret;
            }

            ret = base::ToHexString(num, option) + ret;
            loop_times++;
        }
    }

    return ret;
}
