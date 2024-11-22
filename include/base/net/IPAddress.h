#pragma once

#ifndef HAS_THREAD
#define HAS_THREAD 0
#endif

#include <base/container/Array.h>
#include <base/stream/ReadOnlySpan.h>
#include <base/stream/Span.h>
#include <base/string/ICanToString.h>
#include <bit>

namespace base
{
    /// @brief IP 地址类型。
    enum class IPAddressType
    {
        IPV4,
        IPV6,
    };

    /// @brief IP 地址。兼容 IPV4 和 IPV6.
    class IPAddress :
        public base::ICanToString
    {
    private:
        base::Array<uint8_t, 16> _ip_address_buffer;
        base::Span _span;
        IPAddressType _type = IPAddressType::IPV4;

    public:
#pragma region 生命周期
        /// @brief 构造一个未指定的 IP 地址。此时表现为 IPV4 的 0.0.0.0.
        IPAddress();

        /// @brief 构造一个未指定的 IP 地址。此时可以指定期望的 IP 地址版本。
        /// 无论是对 IPV4 还是 IPV6，构造出来的地址的所有字节都是 0.
        /// @param type
        IPAddress(IPAddressType type);

        /// @brief 构造一个 IPV4 地址。
        /// @param endian ip_address_buffer 中 IP 地址的字节序。
        /// @param ip_address_buffer 存放着 IPV4 地址的缓冲区。
        IPAddress(std::endian endian, base::Array<uint8_t, 4> const &ip_address_buffer);

        /// @brief 构造一个 IPV6 地址。
        /// @param endian ip_address_buffer 中 IP 地址的字节序。
        /// @param ip_address_buffer 存放着 IPV6 地址的缓冲区。
        IPAddress(std::endian endian, base::Array<uint8_t, 16> const &ip_address_buffer);

        /// @brief 构造一个 IP 地址。
        /// @note 是 IPV4 还是 IPV6 取决于初始化列表的大小。初始化列表如果是 4 字节，则构造出来
        /// 是 IPV4 地址，如果是 16 字节，则构造出来是 IPV6 地址。如果都不是，则会抛出异常。
        /// @param endian 初始化列表中的 IP 地址的字节序。
        /// @param list 储存着 IP 地址的初始化列表。
        IPAddress(std::endian endian, std::initializer_list<uint8_t> const &list);

        /// @brief 从 ReadOnlySpan 构造 IP 地址。
        ///
        /// @param endian span 中 IP 地址的字节序。
        ///
        /// @param span 储存着 IP 地址的一段内存。
        /// @note 构造时不是引用这段内存，而是将这段内存中的数据拷贝过来。
        IPAddress(std::endian endian, base::ReadOnlySpan const &span);

        /// @brief 拷贝构造函数。
        /// @param o
        IPAddress(IPAddress const &o);

        /// @brief 赋值运算符。
        /// @param o
        /// @return
        IPAddress &operator=(IPAddress const &o);
#pragma endregion

        uint8_t &operator[](int index);
        uint8_t const &operator[](int index) const;

        /// @brief IP 地址的类型。
        /// @return
        IPAddressType Type() const;

        /// @brief 转化为字符串
        /// @return
        std::string ToString() const override;
    };

#if HAS_THREAD
    /// @brief 测试 IPAddressType
    void TestIpAddress();
#endif
} // namespace base
