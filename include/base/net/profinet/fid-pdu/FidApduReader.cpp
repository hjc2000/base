#include "FidApduReader.h"

base::profinet::FidApduReader::FidApduReader(base::ReadOnlySpan const &span)
	: _ethernet_frame_reader(span)
{
	_this_span = _ethernet_frame_reader.Payload();
}

base::profinet::FrameIdEnum base::profinet::FidApduReader::FrameId() const
{
	uint16_t value = base::big_endian_remote_converter.FromBytes<uint16_t>(_this_span.Slice(base::Range{0, 2}));
	return static_cast<base::profinet::FrameIdEnum>(value);
}

base::ReadOnlySpan base::profinet::FidApduReader::Payload() const
{
	return _this_span.Slice(base::Range{2, _this_span.Size()});
}
