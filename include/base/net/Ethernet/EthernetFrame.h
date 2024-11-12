#pragma once
#include <base/net/Ethernet/enum/LengthTypeEnum.h>
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
        public:
            /// @brief 构造函数
            /// @param span 引用的内存。
            EthernetFrame(base::Span span);

            /// @brief 前导码。
            inline static uint8_t constinit _preamble[7] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA};

            /// @brief 帧起始符。
            inline static uint8_t constinit _frame_start_character = 0xAB;

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

            /// @brief 类型或长度。
            /// @note 整型值小于等于 1500，则表示长度，大于 1500 则表示帧类型。当含义是帧类型时，
            /// 这个值是用来给上层的处理程序看的，让上层的处理程序决定将以太网帧送往哪个协议处理程序。
            /// 例如下面这几个值都大于 1500：
            /// 	@li 0x0800：表示IPv4数据包
            /// 	@li 0x0806：表示ARP请求
            /// 	@li 0x86DD：表示IPv6数据包
            ///
            /// @return
            LengthTypeEnum TypeOrLength() const;
            void SetTypeOrLength(LengthTypeEnum value);

            /// @brief 载荷数据。
            /// @note 最大大小 1500 字节。
            /// @note 如果不满 46 字节，需要后面填充 0，使其达到 46 字节。
            /// @return
            base::Span Payload() const;
            void SetPayload(base::Span const &value);

            /// @brief 冗余校验序列。大小：4 字节。
            /// @return
            base::Span FrameCheckSequence() const;
            void SetFrameCheckSequence(base::Span const &value);
        };
    } // namespace ethernet
} // namespace base
