#pragma once
#include "base/stream/ReadOnlySpan.h"
#include <base/bit/AutoBitConverter.h>
#include <base/net/ethernet/EthernetFrameWriter.h>
#include <base/net/profinet/fid-pdu/FrameIdEnum.h>

namespace base
{
	namespace profinet
	{
		/// @brief 带有帧 ID 的应用层协议数据单元。
		class FidApdu
		{
		private:
			base::ethernet::EthernetFrameWriter _ethernet_frame;
			base::Span _this_span;
			base::AutoBitConverter _converter{std::endian::big};

		public:
			/// @brief 构造函数。
			/// @param span 整个以太网帧的内存片段。
			FidApdu(base::Span const &span);

			/// @brief 目的 MAC 地址。
			/// @return
			base::Mac DestinationMac() const
			{
				return _ethernet_frame.DestinationMac();
			}

			void WriteDestinationMac(base::Mac const &value)
			{
				_ethernet_frame.WriteDestinationMac(value);
			}

			/// @brief 源 MAC 地址。
			/// @return
			base::Mac SourceMac() const
			{
				return _ethernet_frame.SourceMac();
			}

			void SetSourceMac(base::Mac const &value)
			{
				_ethernet_frame.SetSourceMac(value);
			}

			base::profinet::FrameIdEnum FrameId() const;
			void SetFrameId(base::profinet::FrameIdEnum value);

			/// @brief 载荷。
			/// @return
			base::Span Payload() const;

		public:
			/// @brief 设置有效载荷的大小。
			void SetValidPayloadSize(int32_t value);

			base::ReadOnlySpan SpanForSending() const
			{
				return _ethernet_frame.SpanForSending();
			}
		};
	} // namespace profinet
} // namespace base
