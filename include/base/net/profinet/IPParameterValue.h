#pragma once
#include <base/net/IPAddress.h>

namespace base
{
    namespace profinet
    {
        class IPParameterValue
        {
        public:
            /// @brief IP 地址。
            /// @note IPV4 地址。
            /// @return
            IPAddress IP() const;

            /// @brief 子网掩码。
            /// @note IPV4 地址。
            /// @return
            IPAddress Subnetmask() const;

            /// @brief 标准网关。
            /// @note IPV4 地址。
            /// @return
            IPAddress StandardGateway() const;
        };
    } // namespace profinet
} // namespace base
