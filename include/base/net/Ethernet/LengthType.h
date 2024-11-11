#pragma once
#include <base/define.h>
#include <cstdint>

namespace base
{
    namespace ethernet
    {
        /// @brief 提供以太网中一些上层协议的类型长度字段。
        class LengthType
        {
        public:
            /// @brief IP 协议的类型长度字段。
            /// @return
            static_function consteval uint16_t IP()
            {
                return 0x0800;
            }

            /// @brief ARP 协议的类型长度字段。
            /// @return
            static_function consteval uint16_t ARP()
            {
                return 0x0806;
            }

            /// @brief VLAN 标签的类型长度字段。
            /// @note VLAN 标签也叫 802.1Q 标签。
            /// @return
            static_function consteval uint16_t VlanTag()
            {
                return 0x8100;
            }

            static_function consteval uint16_t Profinet()
            {
                return 0x8892;
            }

            static_function consteval uint16_t MRP()
            {
                return 0x88E3;
            }

            static_function consteval uint16_t LLDP()
            {
                return 0x88CC;
            }
        };

    } // namespace ethernet
} // namespace base
