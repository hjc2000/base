#include "FidApdu.h"
#include <base/stream/ReadOnlySpan.h>

base::profinet::FidApdu::FidApdu(base::ethernet::EthernetFrame const &ethernet_frame)
{
	_ethernet_frame = ethernet_frame;
}

base::Span base::profinet::FidApdu::Span() const
{
	// 以太网帧的载荷就是 FidApdu 的全部。
	return _ethernet_frame.Payload();
}

void base::profinet::FidApdu::ConfigureLowlayer()
{
	_ethernet_frame.SetTypeOrLength(base::ethernet::LengthTypeEnum::Profinet);
}

base::profinet::FrameIdEnum base::profinet::FidApdu::FrameId() const
{
	uint16_t value = _converter.ToUInt16(Span().Slice(base::Range{0, 2}));
	return static_cast<base::profinet::FrameIdEnum>(value);
}

void base::profinet::FidApdu::SetFrameId(base::profinet::FrameIdEnum value)
{
	_converter.GetBytes(static_cast<uint16_t>(value), Span().Slice(base::Range{0, 2}));
}

base::Span base::profinet::FidApdu::Payload() const
{
	return Span().Slice(base::Range(2, Span().Size()));
}

void base::profinet::FidApdu::SetValidPayloadSize(int32_t value)
{
	_valid_frame_size = 2 + value;
	_ethernet_frame.SetValidPayloadSize(_valid_frame_size);
}
