#pragma once
#include <base/net/Mac.h>
#include <base/stream/Span.h>
#include <cstdint>

namespace base
{
    /// @brief 以太网帧
    class EthernetFrame
    {
    public:
        /// @brief 构造函数
        /// @param span 引用的内存。
        /// @note 通过解析引用的内存，为一些字段赋值，并尽可能避免内存复制。例如 _payload 字段会直接
        /// 用 span 的 Slice 方法切片出一个小 Span 而不是将载荷复制到一个数组中。
        EthernetFrame(base::Span span);

        /// @brief 前导码。
        inline static uint8_t constinit _preamble[7] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA};

        /// @brief 帧起始符。
        inline static uint8_t constinit _frame_start_character = 0xAB;

        /// @brief 目的 MAC 地址。
        base::Mac _destination_mac;

        /// @brief 源 MAC 地址。
        base::Mac _source_mac;

        /// @brief 802.1Q标签。大小：4 字节。
        base::Span _802_1q_tag;

        /// @brief 类型或长度。
        /// @note 整型值小于等于 1500，则表示长度，大于 1500 则表示帧类型。当含义是帧类型时，
        /// 这个值是用来给上层的处理程序看的，让上层的处理程序决定将以太网帧送往哪个协议处理程序。
        /// 例如下面这几个值都大于 1500：
        /// 	@li 0x0800：表示IPv4数据包
        /// 	@li 0x0806：表示ARP请求
        /// 	@li 0x86DD：表示IPv6数据包
        uint16_t _type_or_length{};

        /// @brief 载荷数据。
        /// @note 最大大小 1500 字节。
        /// @note 如果不满 46 字节，需要后面填充 0，使其达到 46 字节。
        base::Span _payload;

        /// @brief 冗余校验序列。大小：4 字节。
        base::Span _frame_check_sequence;
    };
} // namespace base
