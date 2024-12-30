#include "DcpHelloRequestPdu.h"

#pragma region 私有属性设置函数

void base::profinet::DcpHelloRequestPdu::SetServiceId(base::profinet::ServiceIdEnum value)
{
	_this_span[0] = static_cast<uint8_t>(value);
}

void base::profinet::DcpHelloRequestPdu::SetServiceType(base::profinet::ServiceTypeEnum value)
{
	_this_span[1] = static_cast<uint8_t>(value);
}

void base::profinet::DcpHelloRequestPdu::SetDataLength(uint16_t value)
{
	base::Span span = _this_span.Slice(base::Range{8, 10});
	_converter.GetBytes(value, span);
}

#pragma endregion

base::profinet::DcpHelloRequestPdu::DcpHelloRequestPdu(base::Span const &span)
	: _fid_apdu(span)
{
	_fid_apdu.SetFrameId(base::profinet::FrameIdEnum::DcpHelloRequest);

	// 一开始 Blocks 为空，只有头部信息。头部长度是 10.
	_fid_apdu.SetValidPayloadSize(10);

	_this_span = _fid_apdu.Payload();
	SetServiceId(base::profinet::ServiceIdEnum::Hello);
	SetServiceType(base::profinet::ServiceTypeEnum::Request);
	_block_stream = std::shared_ptr<base::MemoryStream>{new base::MemoryStream{Blocks()}};
}

base::profinet::ServiceIdEnum base::profinet::DcpHelloRequestPdu::ServiceId() const
{
	return static_cast<base::profinet::ServiceIdEnum>(_this_span[0]);
}

base::profinet::ServiceTypeEnum base::profinet::DcpHelloRequestPdu::ServiceType() const
{
	return static_cast<base::profinet::ServiceTypeEnum>(_this_span[1]);
}

uint32_t base::profinet::DcpHelloRequestPdu::Xid() const
{
	base::Span span = _this_span.Slice(base::Range{2, 6});
	return _converter.ToUInt32(span);
}

void base::profinet::DcpHelloRequestPdu::SetXid(uint32_t value)
{
	base::Span span = _this_span.Slice(base::Range{2, 6});
	_converter.GetBytes(value, span);
}

uint16_t base::profinet::DcpHelloRequestPdu::DataLength() const
{
	base::Span span = _this_span.Slice(base::Range{8, 10});
	return _converter.ToUInt16(span);
}

base::Span base::profinet::DcpHelloRequestPdu::Blocks() const
{
	return _this_span.Slice(base::Range{10, _this_span.Size()});
}

void base::profinet::DcpHelloRequestPdu::ClearAllBlocks()
{
	_block_stream->Clear();
	_fid_apdu.SetValidPayloadSize(10 + _block_stream->Length());
}

void base::profinet::DcpHelloRequestPdu::PutNameOfStationBlock(std::string const &station_name)
{
	uint8_t option = 2;
	_block_stream->Write(&option, 0, 1);

	uint8_t suboption = 2;
	_block_stream->Write(&suboption, 0, 1);

	// 2 字节的 block_infos 加上实际的名称长度。
	uint16_t dcp_block_length = 2 + station_name.size();
	_converter.GetBytes(dcp_block_length, *_block_stream);

	// 保留。始终为 0.
	uint16_t block_info = 0;
	_converter.GetBytes(block_info, *_block_stream);

	_converter.GetBytes(station_name, *_block_stream);

	if (station_name.size() % 2 != 0)
	{
		// 名称如果没有 2 字节对齐，需要填充。
		uint8_t padding = 0;
		_block_stream->Write(&padding, 0, 1);
	}

	// 头部长度 10 字节加上 Blocks 的长度。
	_fid_apdu.SetValidPayloadSize(10 + _block_stream->Length());
}
