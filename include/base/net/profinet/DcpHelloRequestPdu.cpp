#include "DcpHelloRequestPdu.h"

void base::profinet::DcpHelloRequestPdu::SetServiceId(base::profinet::ServiceIdEnum value)
{
	base::Span span = _this_span.Slice(0, 1);
	span[0] = static_cast<uint8_t>(value);
}

base::profinet::DcpHelloRequestPdu::DcpHelloRequestPdu(base::Span const &span)
	: _fid_apdu(span)
{
	_fid_apdu.SetFrameId(base::profinet::FrameIdEnum::DcpHelloRequest);
	_this_span = _fid_apdu.Payload();
}

base::profinet::ServiceIdEnum base::profinet::DcpHelloRequestPdu::ServiceId() const
{
	base::Span span = _this_span.Slice(0, 1);
	return static_cast<base::profinet::ServiceIdEnum>(span[0]);
}
