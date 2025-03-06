#pragma once
#include "base/stream/ReadOnlySpan.h"
#include <base/net/IPAddress.h>
#include <base/net/profinet/dcp/DcpServiceIdEnum.h>
#include <base/net/profinet/dcp/DcpServiceTypeEnum.h>
#include <base/net/profinet/fid-pdu/FidApdu.h>
#include <base/stream/MemoryStream.h>

namespace base
{
	namespace profinet
	{
		/// @brief DCP Hello 请求作者。
		class DcpHelloRequestWriter
		{
		private:
			base::profinet::FidApdu _fid_apdu;
			base::Span _this_span;
			std::shared_ptr<base::MemoryStream> _block_stream;

			void UpdateSize();

		public:
			/// @brief 构造函数。
			/// @param span 以太网的发送缓冲区。
			DcpHelloRequestWriter(base::Span const &span);

			/// @brief 源 MAC 地址。
			/// @return
			base::Mac SourceMac() const
			{
				return _fid_apdu.SourceMac();
			}

			/// @brief 设置源 MAC 地址。
			/// @param value
			void WriteSourceMac(base::Mac const &value)
			{
				_fid_apdu.WriteSourceMac(value);
			}

			base::profinet::DcpServiceIdEnum ServiceId() const;
			base::profinet::DcpServiceTypeEnum ServiceType() const;

			uint32_t Xid() const;
			void SetXid(uint32_t value);

			/// @brief Blocks 的有效数据的长度。
			/// @return
			uint16_t DataLength() const;

			/// @brief 删除 Blocks 区域的所有块。
			void ClearAllBlocks();

			/// @brief 放置描述站点名称的块。
			/// @param station_name
			void PutNameOfStationBlock(std::string const &station_name);

			/// @brief 放置 IP 地址信息块。
			/// @param ip_not_set
			/// @param ip
			/// @param gateway
			/// @param netmask
			void PutIPAddressInfomationBlock(bool ip_not_set,
											 base::IPAddress const &ip,
											 base::IPAddress const &gateway,
											 base::IPAddress const &netmask);

			void PutIdBlock(uint16_t vendor_id, uint16_t device_id);

			void PutOemIdBlock(uint16_t oem_vendor_id, uint16_t oem_device_id);

			/// @brief 放置 “设备主动性” 块。
			/// @param hello 设备是否会在上电后主动发送 DCP-Hllo.
			void PutDeviceInitiativeBlock(bool hello);

			/// @brief 整个以太网帧缓冲区中的有效数据 span.
			/// @return
			base::ReadOnlySpan SpanForSending() const
			{
				return _fid_apdu.SpanForSending();
			}
		};
	} // namespace profinet
} // namespace base
