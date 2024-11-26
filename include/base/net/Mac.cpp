#include "Mac.h"
#include <base/bit/AutoBitConverter.h>
#include <base/string/ToHexString.h>

#pragma region 构造函数

base::Mac::Mac(base::Array<uint8_t, 6> const &mac_buffer)
{
    _mac_buffer = mac_buffer;
}

base::Mac::Mac(std::endian endian, base::Array<uint8_t, 6> const &mac_buffer)
{
    _mac_buffer = mac_buffer;
    if (std::endian::little != endian)
    {
        // 保存到本数组中的 MAC 地址要是小端序，如果传进来的是大端序，需要翻转。
        _mac_buffer.Reverse();
    }
}

base::Mac::Mac(std::endian endian, base::ReadOnlySpan const &span)
{
    base::Span buffer{_mac_buffer.Buffer(), _mac_buffer.Count()};
    buffer.CopyFrom(span);
    if (std::endian::little != endian)
    {
        // 保存到本数组中的 MAC 地址要是小端序，如果传进来的是大端序，需要翻转。
        _mac_buffer.Reverse();
    }
}

base::Mac::Mac(Mac const &o)
{
    _mac_buffer = o._mac_buffer;
}

#pragma endregion

base::Mac &base::Mac::operator=(Mac const &o)
{
    _mac_buffer = o._mac_buffer;
    return *this;
}

base::Array<uint8_t, 6> const &base::Mac::InternalArray() const
{
    return _mac_buffer;
}

base::Mac::operator base::Array<uint8_t, 6>() const
{
    return _mac_buffer;
}

base::Mac::operator uint64_t() const
{
    /* _mac_buffer 中的数据此时被当作远程字节序，也是小端序。转换成整型，需要根据本机字节序
     * 决定是否需要翻转。
     */
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

std::string base::Mac::ToString() const
{
    std::string ret{};
    bool first_loop = true;

    base::ToHexStringOption option{};
    option.with_0x_prefix = false;
    option.width = 2;

    for (uint8_t value : _mac_buffer)
    {
        if (first_loop)
        {
            first_loop = false;
            ret = base::ToHexString(value, option);
        }
        else
        {
            ret = base::ToHexString(value, option) + '-' + ret;
        }
    }

    return ret;
}

base::ReadOnlySpan base::Mac::AsReadOnlySpan() const
{
    return base::ReadOnlySpan{_mac_buffer.Buffer(), _mac_buffer.Count()};
}

base::Span base::Mac::AsSpan()
{
    return base::Span{_mac_buffer.Buffer(), _mac_buffer.Count()};
}
