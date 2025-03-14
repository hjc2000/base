#include "DcpHeaderWriter.h"
#include <base/string/define.h>
#include <stdexcept>

base::profinet::DcpHeaderWriter::DcpHeaderWriter(base::Span const &span)
{
	if (span.Size() < 10)
	{
		throw std::invalid_argument{CODE_POS_STR + "传入的 span 的大小必须 >= 10."};
	}

	_span = span;
}

base::profinet::DcpServiceIdEnum base::profinet::DcpHeaderWriter::ServiceId() const
{
	return static_cast<base::profinet::DcpServiceIdEnum>(_span[0]);
}

void base::profinet::DcpHeaderWriter::SetServiceId(base::profinet::DcpServiceIdEnum value)
{
	_span[0] = static_cast<uint8_t>(value);
}

base::profinet::DcpServiceTypeEnum base::profinet::DcpHeaderWriter::ServiceType() const
{
	return static_cast<base::profinet::DcpServiceTypeEnum>(_span[1]);
}

void base::profinet::DcpHeaderWriter::SetServiceType(base::profinet::DcpServiceTypeEnum value)
{
	_span[1] = static_cast<uint8_t>(value);
}

uint32_t base::profinet::DcpHeaderWriter::Xid() const
{
	base::Span span = _span.Slice(base::Range{2, 6});
	return _converter.ToUInt32(span);
}

void base::profinet::DcpHeaderWriter::SetXid(uint32_t value)
{
	base::Span span = _span.Slice(base::Range{2, 6});
	_converter.GetBytes(value, span);
}

uint16_t base::profinet::DcpHeaderWriter::ResponseDelay() const
{
	base::Span span = _span.Slice(base::Range{6, 8});
	return _converter.ToUInt32(span);
}

void base::profinet::DcpHeaderWriter::SetResponseDelay(uint16_t value)
{
	base::Span span = _span.Slice(base::Range{6, 8});
	_converter.GetBytes(value, span);
}

uint16_t base::profinet::DcpHeaderWriter::DataLength() const
{
	base::Span span = _span.Slice(base::Range{8, 10});
	return _converter.ToUInt16(span);
}

void base::profinet::DcpHeaderWriter::SetDataLength(uint16_t value)
{
	base::Span span = _span.Slice(base::Range{8, 10});
	_converter.GetBytes(value, span);
}
