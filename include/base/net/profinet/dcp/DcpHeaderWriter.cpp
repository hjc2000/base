#include "DcpHeaderWriter.h"
#include "base/bit/AutoBitConverter.h"
#include "base/string/define.h"
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
	return base::big_endian_remote_converter.FromBytes<uint32_t>(span);
}

void base::profinet::DcpHeaderWriter::SetXid(uint32_t value)
{
	base::Span span = _span.Slice(base::Range{2, 6});
	base::big_endian_remote_converter.GetBytes(value, span);
}

uint16_t base::profinet::DcpHeaderWriter::ResponseDelay() const
{
	base::Span span = _span.Slice(base::Range{6, 8});
	return base::big_endian_remote_converter.FromBytes<uint16_t>(span);
}

void base::profinet::DcpHeaderWriter::SetResponseDelay(uint16_t value)
{
	base::Span span = _span.Slice(base::Range{6, 8});
	base::big_endian_remote_converter.GetBytes(value, span);
}

uint16_t base::profinet::DcpHeaderWriter::DataLength() const
{
	base::Span span = _span.Slice(base::Range{8, 10});
	return base::big_endian_remote_converter.FromBytes<uint16_t>(span);
}

void base::profinet::DcpHeaderWriter::SetDataLength(uint16_t value)
{
	base::Span span = _span.Slice(base::Range{8, 10});
	base::big_endian_remote_converter.GetBytes(value, span);
}
