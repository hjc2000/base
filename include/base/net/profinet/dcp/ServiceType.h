#pragma once
#include <base/define.h>
#include <cstdint>

namespace base
{
    namespace profinet
    {
        /// @brief 服务类型
        class ServiceType
        {
        public:
            /// @brief 请求。
            /// @return
            static_function consteval uint8_t Request()
            {
                return 0x00;
            }

            /// @brief 响应，并且成功。
            /// @return
            static_function consteval uint8_t ResponseSuccess()
            {
                return 0x01;
            }

            /// @brief 响应。请求不被支持。
            /// @return
            static_function consteval uint8_t ResponseNotSupport()
            {
                return 0x05;
            }
        };
    } // namespace profinet
} // namespace base
