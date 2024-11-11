#include "Mac.h"
#include <base/bit/AutoBitConverter.h>

base::Mac::Mac(base::Array<uint8_t, 6> const &mac_buffer)
{
    _mac_buffer = mac_buffer;
}

base::Mac::Mac(Mac const &o)
{
    _mac_buffer = o._mac_buffer;
}

base::Mac &base::Mac::operator=(Mac const &o)
{
    _mac_buffer = o._mac_buffer;
    return *this;
}

base::Mac::operator base::Array<uint8_t, 6>() const
{
    return _mac_buffer;
}

base::Mac::operator uint64_t() const
{
    base::AutoBitConverter converter{std::endian::little};
    uint64_t value = converter.ToUInt64(_mac_buffer.Buffer(), 0);
    return value;
}

uint8_t &base::Mac::operator[](int index)
{
    return _mac_buffer[index];
}

uint8_t const &base::Mac::operator[](int index) const
{
    return _mac_buffer[index];
}

base::Array<uint8_t, 3> base::Mac::Oui() const
{
    return base::Array<uint8_t, 3>{_mac_buffer.Buffer(), 3, 3};
}

void base::Mac::SetOui(base::Array<uint8_t, 3> const &value)
{
    _mac_buffer.CopyFrom(3, value.Buffer(), 0, value.Count());
}

bool base::Mac::IsMulticastAddress() const
{
    // 最高字节的最低位为 1 则是多播地址，为 0 则是单播地址。
    return _mac_buffer[5] & 0x01;
}
