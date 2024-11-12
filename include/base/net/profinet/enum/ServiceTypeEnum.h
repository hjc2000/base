#pragma once
#include <cstdint>

namespace base
{
    namespace profinet
    {
        /// @brief 服务类型
        enum class ServiceTypeEnum : uint8_t
        {
            /// @brief 请求。
            Request = 0x00,

            /// @brief 响应，并且请求成功。
            ResponseSuccess = 0x01,

            /// @brief 响应，请求不被支持。
            ResponseNotSupport = 0x05,
        };
    } // namespace profinet
} // namespace base
