#pragma once
#include <base/container/Array.h>
#include <base/stream/Span.h>
#include <bit>

namespace base
{
    enum class IPAddressType
    {
        IPV4,
        IPV6,
    };

    /// @brief IP 地址。兼容 IPV4 和 IPV6.
    class IPAddress
    {
    private:
        base::Array<uint8_t, 16> _ip_address_buffer;
        base::Span _span;
        IPAddressType _type = IPAddressType::IPV4;

    public:
        /// @brief 构造一个 IPV4 地址。
        /// @param endian ip_address_buffer 中 IP 地址的字节序。
        /// @param ip_address_buffer 存放着 IPV4 地址的缓冲区。
        IPAddress(std::endian endian, base::Array<uint8_t, 4> const &ip_address_buffer);

        /// @brief 构造一个 IPV6 地址。
        /// @param endian ip_address_buffer 中 IP 地址的字节序。
        /// @param ip_address_buffer 存放着 IPV6 地址的缓冲区。
        IPAddress(std::endian endian, base::Array<uint8_t, 16> const &ip_address_buffer);

        uint8_t &operator[](int index);
    };
} // namespace base
