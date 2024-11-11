#pragma once
#include <base/define.h>
#include <cstdint>

namespace base
{
    namespace profinet
    {
        namespace dcp
        {
            /// @brief DCP 请求帧中的服务 ID.
            class ServiceId
            {
            public:
                static_function consteval uint8_t Get()
                {
                    return 0x03;
                }

                static_function consteval uint8_t Set()
                {
                    return 0x04;
                }

                static_function consteval uint8_t Identify()
                {
                    return 0x05;
                }

                static_function consteval uint8_t Hello()
                {
                    return 0x06;
                }
            };
        } // namespace dcp
    } // namespace profinet
} // namespace base
