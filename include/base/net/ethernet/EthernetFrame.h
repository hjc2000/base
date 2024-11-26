#pragma once
#include <base/net/ethernet/enum/LengthTypeEnum.h>
#include <base/net/Mac.h>
#include <base/stream/Span.h>
#include <cstdint>

namespace base
{
    namespace ethernet
    {
        /// @brief 以太网帧
        class EthernetFrame
        {
        private:
            base::Span _span;
            bool _has_vlan_tag = false;

        public:
            /// @brief 构造函数。
            /// @param span 引用的内存。
            EthernetFrame(base::Span const &span);

            /// @brief 目的 MAC 地址。
            /// @return
            base::Mac DestinationMac() const;
            void SetDestinationMac(base::Mac const &value);

            /// @brief 源 MAC 地址。
            /// @return
            base::Mac SourceMac() const;
            void SetSourceMac(base::Mac const &value);

            /// @brief 802.1Q标签。大小：4 字节。
            /// @return
            base::Span VlanTag() const;
            void SetVlanTag(base::Span const &value);

            /// @brief 是否具有 VLAN TAG.
            /// @return
            bool HasVlanTag() const;

            /// @brief 设置本以太网帧是否具有 VLAN TAG.
            /// @note 当设置为有时，从类型长度字段开始往后的字段都要往后偏移 4 个字节，
            /// 为 VLAN TAG 留出空间，否则就不留出空间。
            /// @warning 设置为 false 后，调用 VlanTag 和 SetVlanTag 方法将引发异常。
            /// 因为设置为 false 后相当于禁用了 VLAN TAG.
            /// @param value
            void SetHasVlanTag(bool value);

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
            LengthTypeEnum TypeOrLength() const;
            void SetTypeOrLength(LengthTypeEnum value);

            /// @brief 载荷数据。
            /// @note 字节数的取值范围：[46, 1500].
            /// @note 巨型帧可以超过 1500 字节。但是需要网络设备支持，否则会导致无法传输。
            /// @note 如果不满 46 字节，需要后面填充 0，使其达到 46 字节。
            /// @note 因为可能会有填充，所以需要靠 TypeOrLength 属性来识别出有效字节数。
            /// @return
            base::Span Payload() const;
            void SetPayload(base::Span const &value);
        };
    } // namespace ethernet
} // namespace base
