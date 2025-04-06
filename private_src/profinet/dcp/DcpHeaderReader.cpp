#include "DcpHeaderReader.h"
#include "base/string/define.h"
#include <stdexcept>

base::profinet::DcpHeaderReader::DcpHeaderReader(base::ReadOnlySpan const &span)
{
	if (span.Size() < 10)
	{
		throw std::invalid_argument{CODE_POS_STR + "传入的 span 的大小必须 >= 10."};
	}

	_span = span;
}

base::profinet::DcpServiceIdEnum base::profinet::DcpHeaderReader::ServiceId() const
{
	return static_cast<base::profinet::DcpServiceIdEnum>(_span[0]);
}

base::profinet::DcpServiceTypeEnum base::profinet::DcpHeaderReader::ServiceType() const
{
	return static_cast<base::profinet::DcpServiceTypeEnum>(_span[1]);
}

uint32_t base::profinet::DcpHeaderReader::Xid() const
{
	base::ReadOnlySpan span = _span.Slice(base::Range{2, 6});
	return _converter.FromBytes<uint32_t>(span);
}

uint16_t base::profinet::DcpHeaderReader::ResponseDelay() const
{
	base::ReadOnlySpan span = _span.Slice(base::Range{6, 8});
	return _converter.FromBytes<uint16_t>(span);
}

uint16_t base::profinet::DcpHeaderReader::DataLength() const
{
	base::ReadOnlySpan span = _span.Slice(base::Range{8, 10});
	return _converter.FromBytes<uint16_t>(span);
}
