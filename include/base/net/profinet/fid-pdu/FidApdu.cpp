#include "FidApdu.h"
#include <base/stream/ReadOnlySpan.h>
#include <base/string/define.h>

base::profinet::FidApdu::FidApdu(base::Span const &span)
	: _ethernet_frame(span)
{
	_ethernet_frame.ClearVlanTag();
	_ethernet_frame.WriteTypeOrLength(base::ethernet::LengthOrTypeEnum::Profinet);
	_this_span = _ethernet_frame.Payload();
}

base::profinet::FrameIdEnum base::profinet::FidApdu::FrameId() const
{
	uint16_t value = _converter.ToUInt16(_this_span.Slice(base::Range{0, 2}));
	return static_cast<base::profinet::FrameIdEnum>(value);
}

void base::profinet::FidApdu::SetFrameId(base::profinet::FrameIdEnum value)
{
	_converter.GetBytes(static_cast<uint16_t>(value), _this_span.Slice(base::Range{0, 2}));
}

base::Span base::profinet::FidApdu::Payload() const
{
	return _this_span.Slice(base::Range{2, _this_span.Size()});
}

void base::profinet::FidApdu::SetValidPayloadSize(int32_t value)
{
	_ethernet_frame.SetValidPayloadSize(2 + value);
}
