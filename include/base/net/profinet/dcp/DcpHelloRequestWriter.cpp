#include "DcpHelloRequestWriter.h"
#include "DcpHeaderWriter.h"
#include "DcpTlvStreamWriter.h"

void base::profinet::DcpHelloRequestWriter::UpdateSize()
{
	base::profinet::DcpHeaderWriter writer{_this_span};
	writer.SetDataLength(_block_stream->Length());

	// 头部长度加上 Blocks 的长度。
	_fid_apdu_writer.SetValidPayloadSize(base::profinet::DcpHeaderWriter::HeaderSize() + _block_stream->Length());
}

base::profinet::DcpHelloRequestWriter::DcpHelloRequestWriter(base::Span const &span)
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
	writer.SetServiceId(base::profinet::DcpServiceIdEnum::Hello);
	writer.SetServiceType(base::profinet::DcpServiceTypeEnum::Request);

	base::Span block_span = _this_span.Slice(base::Range{base::profinet::DcpHeaderWriter::HeaderSize(), _this_span.Size()});
	_block_stream = std::shared_ptr<base::MemoryStream>{new base::MemoryStream{block_span}};
}

base::profinet::DcpServiceIdEnum base::profinet::DcpHelloRequestWriter::ServiceId() const
{
	base::profinet::DcpHeaderWriter writer{_this_span};
	return writer.ServiceId();
}

base::profinet::DcpServiceTypeEnum base::profinet::DcpHelloRequestWriter::ServiceType() const
{
	base::profinet::DcpHeaderWriter writer{_this_span};
	return writer.ServiceType();
}

uint32_t base::profinet::DcpHelloRequestWriter::Xid() const
{
	base::profinet::DcpHeaderWriter writer{_this_span};
	return writer.Xid();
}

void base::profinet::DcpHelloRequestWriter::WriteXid(uint32_t value)
{
	base::profinet::DcpHeaderWriter writer{_this_span};
	writer.SetXid(value);
}

uint16_t base::profinet::DcpHelloRequestWriter::DataLength() const
{
	base::profinet::DcpHeaderWriter writer{_this_span};
	return writer.DataLength();
}

void base::profinet::DcpHelloRequestWriter::ClearAllBlocks()
{
	base::profinet::DcpHeaderWriter writer{_this_span};
	writer.SetDataLength(0);
	_block_stream->Clear();

	// Blocks 区的有效数据长度为 0，只剩下头部是有效数据。
	_fid_apdu_writer.SetValidPayloadSize(base::profinet::DcpHeaderWriter::HeaderSize());
}

void base::profinet::DcpHelloRequestWriter::WriteNameOfStationBlock(std::string const &station_name)
{
	base::profinet::DcpTlvStreamWriter writer{*_block_stream};
	writer.WriteNameOfStationBlock(station_name);
	UpdateSize();
}

void base::profinet::DcpHelloRequestWriter::WriteIPAddressInfomationBlock(bool ip_not_set,
																		  base::IPAddress const &ip,
																		  base::IPAddress const &gateway,
																		  base::IPAddress const &netmask)
{
	base::profinet::DcpTlvStreamWriter writer{*_block_stream};
	writer.WriteIPAddressInfomationBlock(ip_not_set, ip, gateway, netmask);
	UpdateSize();
}

void base::profinet::DcpHelloRequestWriter::WriteIdBlock(uint16_t vendor_id, uint16_t device_id)
{
	base::profinet::DcpTlvStreamWriter writer{*_block_stream};
	writer.WriteIdBlock(vendor_id, device_id);
	UpdateSize();
}

void base::profinet::DcpHelloRequestWriter::WriteOemIdBlock(uint16_t oem_vendor_id, uint16_t oem_device_id)
{
	base::profinet::DcpTlvStreamWriter writer{*_block_stream};
	writer.WriteOemIdBlock(oem_vendor_id, oem_device_id);
	UpdateSize();
}

void base::profinet::DcpHelloRequestWriter::WriteDeviceInitiativeBlock(bool hello)
{
	base::profinet::DcpTlvStreamWriter writer{*_block_stream};
	writer.WriteDeviceInitiativeBlock(hello);
	UpdateSize();
}
