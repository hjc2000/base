#pragma once
#include <base/net/profinet/NameOfStationType.h>

namespace base
{
    namespace profinet
    {
        class NameOfStationBlockRes
        {
        private:
            base::Span _span;

        public:
            NameOfStationBlockRes() = default;
            NameOfStationBlockRes(base::Span const &span);

            base::Span &Span();
            base::Span const &Span() const;

            base::profinet::NameOfStationType NameOfStationType() const;

            /// @brief DCP Block Length
            /// @return
            uint16_t BlockLength() const;

            /// @brief DCP Block Info
            /// @return
            uint16_t BlockInfo() const;

            /// @brief 设备名称字符串。长度范围：[1, 240]
            /// @return
            base::Span Name() const;
        };
    } // namespace profinet
} // namespace base
