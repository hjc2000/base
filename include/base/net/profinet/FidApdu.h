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
			base::AutoBitConverter _converter{std::endian::big};
			int _valid_frame_size = 0;

		public:
			FidApdu() = default;
			FidApdu(base::ethernet::EthernetFrame const &ethernet_frame);

			base::Span Span() const;

			/// @brief 初始化。初始化之后才能开始写本类的属性。
			/// @note 作用是将以太网帧配置为传输 FidApdu.
			void Initialize();

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
