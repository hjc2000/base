#pragma once
#include <base/bit/AutoBitConverter.h>
#include <base/net/ethernet/EthernetFrameWriter.h>
#include <base/net/profinet/enum/FrameIdEnum.h>

namespace base
{
	namespace profinet
	{
		/// @brief 带有帧 ID 的应用层协议数据单元。
		class FidApdu
		{
		private:
			base::ethernet::EthernetFrame _ethernet_frame;
			base::Span _this_span;
			base::AutoBitConverter _converter{std::endian::big};

		public:
			/// @brief 构造函数。
			/// @param span 以太网的发送缓冲区。将以太网缓冲区交给本类。本类会自己组装出
			/// 以太网帧。因为怎么利用以太网发送本类对象，本类最清楚。
			FidApdu(base::Span const &span);

			/// @brief 目的 MAC 地址。
			/// @return
			base::Mac DestinationMac() const
			{
				return _ethernet_frame.DestinationMac();
			}

			void SetDestinationMac(base::Mac const &value)
			{
				_ethernet_frame.SetDestinationMac(value);
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

			/// @brief 设置有效载荷的大小。
			void SetValidPayloadSize(int32_t value);

			/// @brief 整个以太网帧缓冲区中的有效数据 span.
			/// @return
			base::Span ValidDataSpan() const
			{
				return _ethernet_frame.ValidDataSpan();
			}
		};
	} // namespace profinet
} // namespace base
