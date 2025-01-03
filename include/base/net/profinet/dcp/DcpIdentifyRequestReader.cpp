#include "DcpIdentifyRequestReader.h"
#include <base/string/define.h>
#include <DcpHeaderReader.h>
#include <DcpTlvReader.h>

base::profinet::DcpIdentifyRequestReader::DcpIdentifyRequestReader(base::ReadOnlySpan const &span)
	: _fid_pdu_reader(span)
{
	_this_span = _fid_pdu_reader.Payload();
}

base::profinet::DcpServiceIdEnum base::profinet::DcpIdentifyRequestReader::ServiceId() const
{
	base::profinet::DcpHeaderReader reader{_this_span};
	return reader.ServiceId();
}

base::profinet::DcpServiceTypeEnum base::profinet::DcpIdentifyRequestReader::ServiceType() const
{
	base::profinet::DcpHeaderReader reader{_this_span};
	return reader.ServiceType();
}

uint32_t base::profinet::DcpIdentifyRequestReader::Xid() const
{
	base::profinet::DcpHeaderReader reader{_this_span};
	return reader.Xid();
}

uint16_t base::profinet::DcpIdentifyRequestReader::ResponseDelay() const
{
	base::profinet::DcpHeaderReader reader{_this_span};
	return reader.ResponseDelay();
}

uint16_t base::profinet::DcpIdentifyRequestReader::DataLength() const
{
	base::profinet::DcpHeaderReader reader{_this_span};
	return reader.DataLength();
}

#pragma region Blocks

bool base::profinet::DcpIdentifyRequestReader::HasNameOfStationBlock() const
{
	base::profinet::DcpTlvReader reader{_this_span.Slice(base::Range{base::profinet::DcpHeaderReader::HeaderSize(), _this_span.Size()})};
	return reader.HasNameOfStationBlock();
}

std::string base::profinet::DcpIdentifyRequestReader::NameOfStation() const
{
	base::profinet::DcpTlvReader reader{_this_span.Slice(base::Range{base::profinet::DcpHeaderReader::HeaderSize(), _this_span.Size()})};
	return reader.NameOfStation();
}

#pragma endregion
