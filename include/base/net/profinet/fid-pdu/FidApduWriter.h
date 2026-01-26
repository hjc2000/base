#pragma once
#include "base/net/ethernet/EthernetFrameWriter.h"
#include "base/net/profinet/fid-pdu/FrameIdEnum.h"
#include "base/stream/ReadOnlySpan.h"

namespace base
{
	namespace profinet
	{
		///
		/// @brief 带有帧 ID 的应用层协议数据单元写入器。
		///
		///
		class FidApduWriter
		{
		private:
			base::ethernet::EthernetFrameWriter _ethernet_frame;
			base::Span _this_span;

		public:
			///
			/// @brief 构造函数。
			///
			/// @param span 整个以太网帧的内存片段。
			///
			FidApduWriter(base::Span const &span);

			///
			/// @brief 写入目的 MAC 地址。
			///
			/// @param value
			///
			void WriteDestinationMac(base::Mac const &value)
			{
				_ethernet_frame.WriteDestinationMac(value);
			}

			///
			/// @brief 写入源 MAC 地址。
			///
			/// @param value
			///
			void WriteSourceMac(base::Mac const &value)
			{
				_ethernet_frame.WriteSourceMac(value);
			}

			///
			/// @brief PROFINET 帧 ID.
			///
			/// @return base::profinet::FrameIdEnum
			///
			base::profinet::FrameIdEnum FrameId() const;

			///
			/// @brief 写入 PROFINET 帧 ID.
			///
			/// @param value
			///
			void WriteFrameId(base::profinet::FrameIdEnum value);

			///
			/// @brief 载荷。
			///
			/// @return base::Span
			///
			base::Span Payload() const;

			///
			/// @brief 设置有效载荷的大小。
			///
			/// @param value
			///
			void SetValidPayloadSize(int32_t value);

			///
			/// @brief 可用来被发送到以太网的内存段。
			///
			/// @return base::ReadOnlySpan
			///
			base::ReadOnlySpan SpanForSending() const
			{
				return _ethernet_frame.SpanForSending();
			}
		};
	} // namespace profinet
} // namespace base
