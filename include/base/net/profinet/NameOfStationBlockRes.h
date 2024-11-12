#pragma once
#include <base/net/profinet/NameOfStationType.h>

namespace base
{
    namespace profinet
    {
        class NameOfStationBlockRes
        {
        public:
            NameOfStationBlockRes() = default;
            NameOfStationBlockRes(base::Span const &span);

            base::profinet::NameOfStationType NameOfStationType() const;
            uint16_t BlockLength() const;
            uint16_t BlockInfo() const;

            /// @brief 设备名称字符串。长度范围：[1, 240]
            /// @return
            base::Span Name() const;
        };
    } // namespace profinet
} // namespace base
