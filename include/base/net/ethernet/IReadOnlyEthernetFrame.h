#pragma once
#include <base/net/ethernet/enum/LengthTypeEnum.h>
#include <base/net/Mac.h>
#include <base/stream/ReadOnlySpan.h>

namespace base
{
    namespace ethernet
    {
        /// @brief 只读的以太网帧。
        class IReadOnlyEthernetFrame
        {
        public:
            /// @brief 目的 MAC 地址。
            /// @return
            virtual base::Mac DestinationMac() const = 0;

            /// @brief 源 MAC 地址。
            /// @return
            virtual base::Mac SourceMac() const = 0;

            /// @brief 802.1Q标签。大小：4 字节。
            /// @return
            virtual base::ReadOnlySpan VlanTag() const = 0;

            /// @brief 类型或长度。
            /// @note 整型值小于等于 1500，则表示长度，大于 1500 则表示帧类型。当含义是帧类型时，
            /// 这个值是用来给上层的处理程序看的，让上层的处理程序决定将以太网帧送往哪个协议处理程序。
            /// @note 1500 的 16 进制：0x05dc.
            /// @note 下面这几个值都大于 1500：
            /// 	@li 0x0800：表示IPv4数据包
            /// 	@li 0x0806：表示ARP请求
            /// 	@li 0x86DD：表示IPv6数据包
            ///
            /// @return
            virtual base::ethernet::LengthTypeEnum TypeOrLength() const = 0;

            /// @brief 载荷数据。
            /// @note 字节数的取值范围：[46, 1500].
            /// @note 巨型帧可以超过 1500 字节。但是需要网络设备支持，否则会导致无法传输。
            /// @note 如果不满 46 字节，需要后面填充 0，使其达到 46 字节。
            /// @note 因为可能会有填充，所以需要靠 TypeOrLength 属性来识别出有效字节数。
            /// @return
            virtual base::ReadOnlySpan Payload() const = 0;
        };
    } // namespace ethernet
} // namespace base
