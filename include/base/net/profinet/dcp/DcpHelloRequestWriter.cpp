#include "DcpHelloRequestWriter.h"
#include <base/string/define.h>
#include <DcpHeaderWriter.h>
#include <DcpTlvStreamWriter.h>

void base::profinet::DcpHelloRequestWriter::UpdateSize()
{
	base::profinet::DcpHeaderWriter writer{_this_span};
	writer.SetDataLength(_block_stream->Length());

	// 头部长度加上 Blocks 的长度。
	_fid_apdu.SetValidPayloadSize(base::profinet::DcpHeaderWriter::Size() + _block_stream->Length());
}

base::profinet::DcpHelloRequestWriter::DcpHelloRequestWriter(base::Span const &span)
	: _fid_apdu(span)
{
	_fid_apdu.SetFrameId(base::profinet::FrameIdEnum::DcpHelloRequest);

	_fid_apdu.SetDestinationMac(base::Mac{
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

	_this_span = _fid_apdu.Payload();

	base::profinet::DcpHeaderWriter writer{_this_span};
	writer.SetServiceId(base::profinet::DcpServiceIdEnum::Hello);
	writer.SetServiceType(base::profinet::DcpServiceTypeEnum::Request);

	base::Span block_span = _this_span.Slice(base::Range{base::profinet::DcpHeaderWriter::Size(), _this_span.Size()});
	_block_stream = std::shared_ptr<base::MemoryStream>{new base::MemoryStream{block_span}};
}

#pragma region DCP 头部

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

void base::profinet::DcpHelloRequestWriter::SetXid(uint32_t value)
{
	base::profinet::DcpHeaderWriter writer{_this_span};
	writer.SetXid(value);
}

uint16_t base::profinet::DcpHelloRequestWriter::DataLength() const
{
	base::profinet::DcpHeaderWriter writer{_this_span};
	return writer.DataLength();
}

#pragma endregion

#pragma region Blocks

void base::profinet::DcpHelloRequestWriter::ClearAllBlocks()
{
	base::profinet::DcpHeaderWriter writer{_this_span};
	writer.SetDataLength(0);
	_block_stream->Clear();

	// Blocks 区的有效数据长度为 0，只剩下头部是有效数据。
	_fid_apdu.SetValidPayloadSize(base::profinet::DcpHeaderWriter::Size());
}

void base::profinet::DcpHelloRequestWriter::PutNameOfStationBlock(std::string const &station_name)
{
	base::profinet::DcpTlvStreamWriter writer{*_block_stream};
	writer.WriteNameOfStationBlock(station_name);
	UpdateSize();
}

void base::profinet::DcpHelloRequestWriter::PutIPAddressInfomationBlock(bool ip_not_set,
																		base::IPAddress const &ip,
																		base::IPAddress const &gateway,
																		base::IPAddress const &netmask)
{
	base::profinet::DcpTlvStreamWriter writer{*_block_stream};
	writer.WriteIPAddressInfomationBlock(ip_not_set, ip, gateway, netmask);
	UpdateSize();
}

void base::profinet::DcpHelloRequestWriter::PutIdBlock(uint16_t vendor_id, uint16_t device_id)
{
	base::profinet::DcpTlvStreamWriter writer{*_block_stream};
	writer.WriteIdBlock(vendor_id, device_id);
	UpdateSize();
}

void base::profinet::DcpHelloRequestWriter::PutOemIdBlock(uint16_t oem_vendor_id, uint16_t oem_device_id)
{
	base::profinet::DcpTlvStreamWriter writer{*_block_stream};
	writer.WriteOemIdBlock(oem_vendor_id, oem_device_id);
	UpdateSize();
}

void base::profinet::DcpHelloRequestWriter::PutDeviceInitiativeBlock(bool hello)
{
	base::profinet::DcpTlvStreamWriter writer{*_block_stream};
	writer.WriteDeviceInitiativeBlock(hello);
	UpdateSize();
}

#pragma endregion
