#include "FidApduWriter.h"
#include "base/stream/Span.h"

base::profinet::FidApduWriter::FidApduWriter(base::Span const &span)
	: _ethernet_frame(span)
{
	_ethernet_frame.ClearVlanTag();
	_ethernet_frame.WriteTypeOrLength(base::ethernet::LengthOrTypeEnum::Profinet);
	_this_span = _ethernet_frame.Payload();
}

base::profinet::FrameIdEnum base::profinet::FidApduWriter::FrameId() const
{
	base::Span span = _this_span.Slice(base::Range{0, 2});
	uint16_t value = _converter.ToUInt16(span);
	return static_cast<base::profinet::FrameIdEnum>(value);
}

void base::profinet::FidApduWriter::WriteFrameId(base::profinet::FrameIdEnum value)
{
	base::Span span = _this_span.Slice(base::Range{0, 2});
	_converter.GetBytes(static_cast<uint16_t>(value), span);
}

base::Span base::profinet::FidApduWriter::Payload() const
{
	return _this_span.Slice(base::Range{2, _this_span.Size()});
}

void base::profinet::FidApduWriter::SetValidPayloadSize(int32_t value)
{
	_ethernet_frame.SetValidPayloadSize(2 + value);
}
