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

			base::profinet::FrameIdEnum FrameId();

			///
			/// @brief 读取载荷数据。
			///
			/// @param span
			///
			void ReadPayload(base::Span const &span)
			{
				_ethernet_frame_reader.ReadPayload(span);
			}

			///
			/// @brief 读取载荷数据。
			///
			/// @param remote_endian
			///
			/// @return
			///
			template <typename ReturnType>
			ReturnType ReadPayload(std::endian remote_endian)
			{
				return _ethernet_frame_reader.ReadPayload<ReturnType>(remote_endian);
			}
		};
	} // namespace profinet
} // namespace base
