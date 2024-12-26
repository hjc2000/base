#pragma once
#include <cstdint>

namespace base
{
	namespace profinet
	{
		enum class FrameIdEnum : uint16_t
		{
			DcpHelloRequest = 0xfefc,
			DcpGetRequest = 0xfefd,
			DcpSetRequest = 0xfefd,
			DcpGetResponse = 0xfefd,
			DcpSetResponse = 0xfefd,
			DcpIdentifyRequest = 0xfefe,
			DcpIdentifyResponse = 0xfeff,
		};
	} // namespace profinet
} // namespace base
