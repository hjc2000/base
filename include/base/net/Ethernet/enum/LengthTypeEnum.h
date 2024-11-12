#pragma once
#include <base/define.h>
#include <cstdint>

namespace base
{
    namespace ethernet
    {
        /// @brief 提供以太网中一些上层协议的类型长度字段。
        enum class LengthTypeEnum : uint16_t
        {
            /// @brief IP 协议的类型长度字段。
            IP = 0x0800,

            /// @brief ARP 协议的类型长度字段。
            ARP = 0x0806,

            /// @brief VLAN 标签的类型长度字段。
            /// @note VLAN 标签也叫 802.1Q 标签。
            VlanTag = 0x8100,

            Profinet = 0x8892,
            MRP = 0x88E3,
            LLDP = 0x88CC,
        };

    } // namespace ethernet
} // namespace base
