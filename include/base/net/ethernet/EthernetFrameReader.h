#pragma once
#include <base/bit/AutoBitConverter.h>
#include <base/net/ethernet/LengthOrTypeEnum.h>
#include <base/net/Mac.h>
#include <base/stream/ReadOnlySpan.h>
#include <base/string/Json.h>

namespace base
{
	namespace ethernet
	{
		/// @brief 只读的以太网帧。
		class EthernetFrameReader :
			public base::IJsonSerializable
		{
		private:
			base::ReadOnlySpan _span;
			base::AutoBitConverter _converter{std::endian::big};

		public:
			/// @brief 引用 span 指向的内存段，在此位置解析以太网帧。
			/// @param span
			EthernetFrameReader(base::ReadOnlySpan const &span);

			/// @brief 目的 MAC 地址。
			/// @return
			base::Mac DestinationMac() const;

			/// @brief 源 MAC 地址。
			/// @return
			base::Mac SourceMac() const;

			/// @brief 802.1Q标签。大小：4 字节。
			/// @return
			base::ReadOnlySpan VlanTag() const;

			/// @brief 是否具有 802.1Q标签。
			/// @return
			bool HasVlanTag() const;

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
			base::ethernet::LengthOrTypeEnum TypeOrLength() const;

			/// @brief 载荷数据。
			/// @note 这里返回的 span 是构造函数中交给本对象的 span 去除以太网头部
			/// 后剩余的全部子 span，用户需要自己根据有效数据的长度去除其中的有效数据，
			/// 本类是以太网帧类，无法识别上层协议中定义的有效数据长度。所以返回的 span
			/// 的大小会大于等于有效数据长度。
			/// @return
			base::ReadOnlySpan Payload() const;

			/// @brief 序列化为 json
			/// @return
			Json ToJson() const override;
		};
	} // namespace ethernet
} // namespace base
