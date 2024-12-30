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

#pragma endregion

base::profinet::DcpHelloRequestPdu::DcpHelloRequestPdu(base::Span const &span)
	: _fid_apdu(span)
{
	_fid_apdu.SetFrameId(base::profinet::FrameIdEnum::DcpHelloRequest);
	_this_span = _fid_apdu.Payload();
	SetServiceId(base::profinet::ServiceIdEnum::Hello);
	SetServiceType(base::profinet::ServiceTypeEnum::Request);
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
