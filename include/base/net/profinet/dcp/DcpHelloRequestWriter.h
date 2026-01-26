#pragma once
#include "base/net/IPAddress.h"
#include "base/net/profinet/dcp/DcpServiceIdEnum.h"
#include "base/net/profinet/dcp/DcpServiceTypeEnum.h"
#include "base/net/profinet/fid-pdu/FidApduWriter.h"
#include "base/stream/MemoryStream.h"
#include "base/stream/ReadOnlySpan.h"
#include "DcpHeaderWriter.h"
#include "DcpTlvStreamWriter.h"

namespace base::profinet
{
	///
	/// @brief DCP Hello 请求写入器。
	///
	class DcpHelloRequestWriter
	{
	private:
		base::profinet::FidApduWriter _fid_apdu_writer;
		base::Span _this_span;
		std::shared_ptr<base::MemoryStream> _block_stream;

		void UpdateSize()
		{
			base::profinet::DcpHeaderWriter writer{_this_span};
			writer.WriteDataLength(_block_stream->Length());
		}

	public:
		///
		/// @brief 构造函数。
		///
		/// @param span 以太网的发送缓冲区。
		///
		DcpHelloRequestWriter(base::Span const &span)
			: _fid_apdu_writer(span)
		{
			_fid_apdu_writer.WriteFrameId(base::profinet::FrameIdEnum::DcpHelloRequest);

			_fid_apdu_writer.WriteDestinationMac(base::Mac{
				std::endian::big,
				base::Array<uint8_t, 6>{
					0x01,
					0x0e,
					0xcf,
					0x00,
					0x00,
					0x01,
				},
			});

			_this_span = _fid_apdu_writer.Payload();

			base::profinet::DcpHeaderWriter writer{_this_span};
			writer.WriteServiceId(base::profinet::DcpServiceIdEnum::Hello);
			writer.WriteServiceType(base::profinet::DcpServiceTypeEnum::Request);

			base::Span block_span = _this_span.Slice(base::Range{base::profinet::DcpHeaderWriter::HeaderSize(), _this_span.Size()});
			_block_stream = std::shared_ptr<base::MemoryStream>{new base::MemoryStream{block_span}};
		}

		///
		/// @brief 设置源 MAC 地址。
		///
		/// @param value
		///
		void WriteSourceMac(base::Mac const &value)
		{
			_fid_apdu_writer.WriteSourceMac(value);
		}

		void WriteXid(uint32_t value)
		{
			base::profinet::DcpHeaderWriter writer{_this_span};
			writer.WriteXid(value);
		}

		///
		/// @brief 删除 Blocks 区域的所有块。
		///
		void ClearAllBlocks()
		{
			base::profinet::DcpHeaderWriter writer{_this_span};
			writer.WriteDataLength(0);
			_block_stream->Clear();
		}

		///
		/// @brief 写入描述站点名称的块。
		///
		/// @param station_name
		///
		void WriteNameOfStationBlock(std::string const &station_name)
		{
			base::profinet::DcpTlvStreamWriter writer{*_block_stream};
			writer.WriteNameOfStationBlock(station_name);
			UpdateSize();
		}

		///
		/// @brief 写入 IP 地址信息块。
		///
		/// @param ip_not_set
		/// @param ip
		/// @param gateway
		/// @param netmask
		///
		void WriteIPAddressInfomationBlock(bool ip_not_set,
										   base::IPAddress const &ip,
										   base::IPAddress const &gateway,
										   base::IPAddress const &netmask)
		{
			base::profinet::DcpTlvStreamWriter writer{*_block_stream};
			writer.WriteIPAddressInfomationBlock(ip_not_set, ip, gateway, netmask);
			UpdateSize();
		}

		///
		/// @brief 写入 ID 块。
		///
		/// @param vendor_id
		/// @param device_id
		///
		void WriteIdBlock(uint16_t vendor_id, uint16_t device_id)
		{
			base::profinet::DcpTlvStreamWriter writer{*_block_stream};
			writer.WriteIdBlock(vendor_id, device_id);
			UpdateSize();
		}

		///
		/// @brief 写入 OEM ID 块。
		///
		/// @param oem_vendor_id
		/// @param oem_device_id
		///
		void WriteOemIdBlock(uint16_t oem_vendor_id, uint16_t oem_device_id)
		{
			base::profinet::DcpTlvStreamWriter writer{*_block_stream};
			writer.WriteOemIdBlock(oem_vendor_id, oem_device_id);
			UpdateSize();
		}

		///
		/// @brief 写入 “设备主动性” 块。
		///
		/// @param hello 设备是否会在上电后主动发送 DCP-Hllo.
		///
		void WriteDeviceInitiativeBlock(bool hello)
		{
			base::profinet::DcpTlvStreamWriter writer{*_block_stream};
			writer.WriteDeviceInitiativeBlock(hello);
			UpdateSize();
		}

		///
		/// @brief 可用来被发送到以太网中的内存段。
		///
		/// @return
		///
		base::ReadOnlySpan SpanForSending() const
		{
			return _fid_apdu_writer.SpanForSending();
		}
	};

} // namespace base::profinet
