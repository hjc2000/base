#pragma once
#include <base/bit/AutoBitConverter.h>
#include <base/net/ethernet/EthernetFrame.h>
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

			base::profinet::FrameIdEnum FrameId() const;
			void SetFrameId(base::profinet::FrameIdEnum value);

			/// @brief 载荷。
			/// @return
			base::Span Payload() const;

			/// @brief 设置有效载荷的大小。
			void SetValidPayloadSize(int32_t value);
		};
	} // namespace profinet
} // namespace base
