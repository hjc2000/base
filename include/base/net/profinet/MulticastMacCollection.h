#pragma once
#include <base/define.h>
#include <base/net/Mac.h>
#include <cstdint>

namespace base
{
    namespace profinet
    {
        /// @brief 多播 MAC 地址集合
        class MulticastMacCollection
        {
        public:
            static_function base::Mac DcpIdentify();
            static_function base::Mac DcpHello();
        };
    } // namespace profinet
} // namespace base
