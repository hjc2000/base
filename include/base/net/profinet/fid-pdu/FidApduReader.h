#pragma once
#include "base/net/ethernet/EthernetFrameReader.h"
#include "base/net/profinet/fid-pdu/FrameIdEnum.h"

namespace base
{
	namespace profinet
	{
		///
		/// @brief 带有帧 ID 的应用层协议数据单元。
		///
		///
		class FidApduReader
		{
		private:
			base::ethernet::EthernetFrameReader _ethernet_frame_reader;
			base::ReadOnlySpan _this_span;

		public:
			///
			/// @brief 构造函数。
			///
			/// @param span 整个以太网帧的内存片段。
			///
			FidApduReader(base::ReadOnlySpan const &span);

			///
			/// @brief 目的 MAC 地址。
			///
			/// @return base::Mac
			///
			base::Mac DestinationMac() const
			{
				return _ethernet_frame_reader.DestinationMac();
			}

			///
			/// @brief 源 MAC 地址。
			///
			/// @return base::Mac
			///
			base::Mac SourceMac() const
			{
				return _ethernet_frame_reader.SourceMac();
			}

			base::profinet::FrameIdEnum FrameId() const;

			///
			/// @brief 载荷。
			///
			/// @return base::ReadOnlySpan
			///
			base::ReadOnlySpan Payload() const;
		};
	} // namespace profinet
} // namespace base
