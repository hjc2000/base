#pragma once
#include <base/net/IPAddress.h>

namespace base
{
    /// @brief IP 终结点。
    class IPEndPoint
    {
    private:
        base::IPAddress _ip_address{};
        uint16_t _port = 0;

    public:
#pragma region life
        /// @brief 无参构造函数。构造出的终结点具有无效的 IP 地址，端口号为 0.
        IPEndPoint() = default;

        /// @brief 通过 IP 地址和端口号构造终结点。
        /// @param ip
        /// @param port
        IPEndPoint(base::IPAddress const &ip, uint16_t port);

        /// @brief 拷贝构造函数。
        /// @param o
        IPEndPoint(IPEndPoint const &o);

        /// @brief 赋值运算符。
        /// @param o
        /// @return
        IPEndPoint &operator=(IPEndPoint const &o);
#pragma endregion

        base::IPAddress IPAddress() const;
        void SetIPAddress(base::IPAddress const &value);

        uint16_t Port() const;
        void SetPort(uint16_t value);
    };
} // namespace base
