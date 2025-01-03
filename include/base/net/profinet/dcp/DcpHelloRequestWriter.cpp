#include "DcpHelloRequestWriter.h"
#include <base/string/define.h>
#include <DcpTlvStreamWriter.h>

#pragma region 私有属性设置函数

void base::profinet::DcpHelloRequestWriter::SetServiceId(base::profinet::DcpServiceIdEnum value)
{
	_this_span[0] = static_cast<uint8_t>(value);
}

void base::profinet::DcpHelloRequestWriter::SetServiceType(base::profinet::DcpServiceTypeEnum value)
{
	_this_span[1] = static_cast<uint8_t>(value);
}

void base::profinet::DcpHelloRequestWriter::SetDataLength(uint16_t value)
{
	base::Span span = _this_span.Slice(base::Range{8, 10});
	_converter.GetBytes(value, span);
}

void base::profinet::DcpHelloRequestWriter::UpdateSize()
{
	SetDataLength(_block_stream->Length());

	// 头部长度 10 字节加上 Blocks 的长度。
	_fid_apdu.SetValidPayloadSize(10 + DataLength());
}

#pragma endregion

void base::profinet::DcpHelloRequestWriter::WriteBlockHeader(uint8_t option, uint8_t suboption, uint16_t block_length, uint16_t block_info)
{
	_block_stream->Write(&option, 0, 1);
	_block_stream->Write(&suboption, 0, 1);
	_converter.GetBytes(block_length, *_block_stream);
	_converter.GetBytes(block_info, *_block_stream);
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
	SetServiceId(base::profinet::DcpServiceIdEnum::Hello);
	SetServiceType(base::profinet::DcpServiceTypeEnum::Request);

	base::Span block_span = _this_span.Slice(base::Range{10, _this_span.Size()});
	_block_stream = std::shared_ptr<base::MemoryStream>{new base::MemoryStream{block_span}};
}

#pragma region DCP 头部

base::profinet::DcpServiceIdEnum base::profinet::DcpHelloRequestWriter::ServiceId() const
{
	return static_cast<base::profinet::DcpServiceIdEnum>(_this_span[0]);
}

base::profinet::DcpServiceTypeEnum base::profinet::DcpHelloRequestWriter::ServiceType() const
{
	return static_cast<base::profinet::DcpServiceTypeEnum>(_this_span[1]);
}

uint32_t base::profinet::DcpHelloRequestWriter::Xid() const
{
	base::Span span = _this_span.Slice(base::Range{2, 6});
	return _converter.ToUInt32(span);
}

void base::profinet::DcpHelloRequestWriter::SetXid(uint32_t value)
{
	base::Span span = _this_span.Slice(base::Range{2, 6});
	_converter.GetBytes(value, span);
}

uint16_t base::profinet::DcpHelloRequestWriter::DataLength() const
{
	base::Span span = _this_span.Slice(base::Range{8, 10});
	return _converter.ToUInt16(span);
}

#pragma endregion

#pragma region Blocks

void base::profinet::DcpHelloRequestWriter::ClearAllBlocks()
{
	SetDataLength(0);
	_block_stream->Clear();

	// Blocks 区的有效数据长度为 0，只剩下头部的 10 字节是有效数据。
	_fid_apdu.SetValidPayloadSize(10);
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
