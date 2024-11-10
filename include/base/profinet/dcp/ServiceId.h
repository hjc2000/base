#pragma once
#include <cstdint>

namespace base
{
    namespace profinet
    {
        namespace dcp
        {
            /// @brief DCP 请求帧中的服务 ID.
            enum class ServiceId : uint8_t
            {
                Get = 0x03,
                Set = 0x04,
                Identify = 0x05,
                Hello = 0x06,
            };
        } // namespace dcp
    } // namespace profinet
} // namespace base
