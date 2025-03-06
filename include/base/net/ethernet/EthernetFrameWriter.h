#pragma once
#include <base/bit/AutoBitConverter.h>
#include <base/net/ethernet/LengthOrTypeEnum.h>
#include <base/net/Mac.h>
#include <base/stream/ReadOnlySpan.h>
#include <cstdint>

namespace base
{
	namespace ethernet
	{
		/**
		 * @brief 以太网帧作者。
		 *
		 * @note 这里的属性最好是从上到下按顺序设置。特别是从 VlanTag 开始，因为 VlanTag 有没有设置
		 * 将会影响到后续属性放置到内存中的位置。也不要在添加或删除了 VlanTag 属性后继续尝试读取 VlanTag
		 * 后面的属性，因为偏移量变了，会读取到错误的结果。
		 */
		class EthernetFrameWriter
		{
		private:
			base::Span _span;
			int _valid_frame_size = 0;
			base::AutoBitConverter _converter{std::endian::big};

		public:
			/**
			 * @brief 构造函数。
			 *
			 * @param span 引用的内存。
			 */
			EthernetFrameWriter(base::Span const &span);

		public:
			/**
			 * @brief 目的 MAC 地址。
			 *
			 * @return base::Mac
			 */
			base::Mac DestinationMac() const;

			/**
			 * @brief 写入目的 MAC 地址。
			 *
			 * @param value
			 */
			void WriteDestinationMac(base::Mac const &value);

			/**
			 * @brief 源 MAC 地址。
			 *
			 * @return base::Mac
			 */
			base::Mac SourceMac() const;

			/**
			 * @brief 写入源 MAC 地址。
			 *
			 * @param value
			 */
			void WriteSourceMac(base::Mac const &value);

			/**
			 * @brief 802.1Q标签。大小：4 字节。
			 *
			 * @return base::Span 如果具有 VLAN TAG，则返回引用这段内存的 Span，否则返回没有引用任何
			 * 内存的空的 Span.
			 */
			base::Span VlanTag() const;

			/**
			 * @brief 写入 802.1Q标签。
			 *
			 * @param value
			 */
			void WriteVlanTag(base::ReadOnlySpan const &value);

			/**
			 * @brief 是否具有 VLAN TAG.
			 *
			 * @return true
			 * @return false
			 */
			bool HasVlanTag() const;

			/**
			 * @brief 将 VLAN TAG 所在的 4 个字节清除，变成 0. 这么做之后，HasVlanTag 属性就会变成 false.
			 *
			 * @note 本函数会先判断 HasVlanTag，只有 HasVlanTag 为 true 时才会将 VLAN TAG 所在的 4 个字节置成 0，
			 * 这可以避免在不含 VLAN TAG 时破坏帧。
			 */
			void ClearVlanTag();

			/**
			 * @brief 类型或长度。
			 *
			 * @note 整型值小于等于 1500，则表示长度，大于 1500 则表示帧类型。当含义是帧类型时，
			 * 这个值是用来给上层的处理程序看的，让上层的处理程序决定将以太网帧送往哪个协议处理程序。
			 *
			 * @note 1500 的 16 进制：0x05dc.
			 *
			 * @note 下面这几个值都大于 1500：
			 *		@li 0x0800：表示IPv4数据包
			 *		@li 0x0806：表示ARP请求
			 *		@li 0x86DD：表示IPv6数据包
			 *
			 * @return LengthOrTypeEnum
			 */
			LengthOrTypeEnum TypeOrLength() const;

			/**
			 * @brief 写入类型或长度。
			 *
			 * @param value
			 */
			void WriteTypeOrLength(LengthOrTypeEnum value);

			/**
			 * @brief 载荷数据。
			 *
			 * @note 字节数的取值范围：[46, 1500].
			 *
			 * @note 巨型帧可以超过 1500 字节。但是需要网络设备支持，否则会导致无法传输。
			 *
			 * @note 如果不满 46 字节，需要后面填充 0，使其达到 46 字节。
			 *
			 * @note 因为可能会有填充，所以需要靠 TypeOrLength 属性来识别出有效字节数。
			 *
			 * @note 这里返回的 Span 是构造函数中交给本对象的 Span 被填充以太网头部后的全部
			 * 剩余空间，并不是实际的有效载荷。本类是以太网帧类，无法识别出有效载荷的长度，这种
			 * 工作只能交给上层。
			 *
			 * @return base::Span
			 */
			base::Span Payload() const;

			/**
			 * @brief 将 span 的数据复制到载荷区中。
			 *
			 * @param span
			 */
			void WritePayload(base::ReadOnlySpan const &span);

		public:
			/**
			 * @brief 设置有效载荷的大小。
			 *
			 * @param value 有效载荷的大小。如果小于 46，会在有效载荷后面填充值为 0 的字节，使载荷达到 46 字节。
			 */
			void SetValidPayloadSize(int32_t value);

			/**
			 * @brief 从整个 span 中切割出有效的可以发送到以太网中的 span.
			 *
			 * @note 切割范围：[0, FrameSize].
			 *
			 * @return base::ReadOnlySpan
			 */
			base::ReadOnlySpan SpanForSending() const;

			/**
			 * @brief 帧大小。有 VLAN TAG 时至少是 64 字节，无 VLAN TAG 时至少是 60 字节。
			 * 载荷的填充字节也被计算在内。
			 *
			 * @note 本属性受 SetValidPayloadSize 方法的影响。
			 *
			 * @return int
			 */
			int FrameSize() const;
		};
	} // namespace ethernet
} // namespace base
