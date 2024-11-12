#pragma once
#include <base/net/Mac.h>
#include <base/stream/Stream.h>
#include <cstdint>

namespace base
{
    /// @brief 以太网帧
    class EthernetFrame
    {
    public:
        /// @brief 从流中反序列化出以太网帧
        /// @param stream
        /// @return
        bool TryDeserialize(base::Stream &stream)
        {
            return false;
        }

        /// @brief 将以太网帧序列化到流中
        /// @param stream
        void Serialize(base::Stream &stream)
        {
        }

        /// @brief 前导码。
        uint8_t _preamble[7] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA};

        /// @brief 帧起始符。
        uint8_t _frame_start_character = 0xAB;

        /// @brief 目的 MAC 地址。
        base::Mac _destination_mac{};

        /// @brief 源 MAC 地址。
        base::Mac _source_mac[6] = {};

        /// @brief 802.1Q标签
        uint8_t _802_1q_tag[4] = {};

        /// @brief 类型或长度。
        /// @note 整型值小于等于 1500，则表示长度，大于 1500 则表示帧类型。当含义是帧类型时，
        /// 这个值是用来给上层的处理程序看的，让上层的处理程序决定将以太网帧送往哪个协议处理程序。
        /// 例如下面这几个值都大于 1500：
        /// 	@li 0x0800：表示IPv4数据包
        /// 	@li 0x0806：表示ARP请求
        /// 	@li 0x86DD：表示IPv6数据包
        uint16_t _type_or_length = {};

        /// @brief 载荷数据。
        /// @note 如果不满 46 字节，需要后面填充 0，使其达到 46 字节。
        uint8_t _payload[1500] = {};

        /// @brief 冗余校验序列。
        uint8_t _frame_check_sequence[4] = {};
    };
} // namespace base
