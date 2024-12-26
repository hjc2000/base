#include "FidApdu.h"
#include <base/stream/ReadOnlySpan.h>

base::profinet::FidApdu::FidApdu(base::Span const &span)
{
	_span = span;
}

base::Span const &base::profinet::FidApdu::Span() const
{
	return _span;
}

base::profinet::FrameIdEnum base::profinet::FidApdu::FrameId() const
{
	uint16_t value = _converter.ToUInt16(_span.Buffer(), 0);
	return static_cast<base::profinet::FrameIdEnum>(value);
}

void base::profinet::FidApdu::SetFrameId(base::profinet::FrameIdEnum value)
{
	_converter.GetBytes(static_cast<uint16_t>(value),
						_span.Slice(0, 2).Buffer(),
						0);
}

base::Span base::profinet::FidApdu::Payload() const
{
	return _span.Slice(base::Range(2, _span.Size()));
}

void base::profinet::FidApdu::SetPayload(base::ReadOnlySpan const &value)
{
	Payload().CopyFrom(value);
	_span.Slice(base::Range{value.Size(), _span.Size()}).FillWithZero();
}
