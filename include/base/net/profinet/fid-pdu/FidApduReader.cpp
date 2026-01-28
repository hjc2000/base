#include "FidApduReader.h"
#include <cstdint>

base::profinet::FidApduReader::FidApduReader(base::ReadOnlySpan const &span)
	: _ethernet_frame_reader{span}
{
}

base::profinet::FrameIdEnum base::profinet::FidApduReader::FrameId()
{
	uint16_t value = _ethernet_frame_reader.ReadPayload<uint16_t>(std::endian::big);
	return static_cast<base::profinet::FrameIdEnum>(value);
}
