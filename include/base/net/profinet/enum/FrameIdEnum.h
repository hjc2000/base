#pragma once
#include <cstdint>

namespace base
{
    namespace profinet
    {
        enum class FrameIdEnum : uint16_t
        {
            DcpHelloRequest = 0xFEFC,
            DcpGetRequest = 0xFEFD,
            DcpSetRequest = 0xFEFD,
            DcpGetResponse = 0xFEFD,
            DcpSetResponse = 0xFEFD,
            DcpIdentifyRequest = 0xFEFE,
            DcpIdentifyResponse = 0xFEFF,
        };
    } // namespace profinet
} // namespace base
