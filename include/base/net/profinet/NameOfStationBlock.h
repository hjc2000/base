#pragma once
#include <base/net/profinet/NameOfStationType.h>

namespace base
{
    namespace profinet
    {
        class NameOfStationBlock
        {
        public:
            NameOfStationBlock() = default;
            NameOfStationBlock(base::Span const &span);

            base::profinet::NameOfStationType Type() const;
            uint16_t BlockLength() const;

            /// @brief 设备名称字符串。长度范围：[1, 240]
            /// @return
            base::Span Name() const;
            void SetName(base::Span const &value);
        };
    } // namespace profinet
} // namespace base
