#pragma once
#include <base/net/profinet/DataItem.h>
#include <base/stream/Span.h>

namespace base
{
    namespace profinet
    {
        class C_SDU
        {
        private:
            base::Span _span;

        public:
            C_SDU() = default;
            C_SDU(base::Span const &span);

            base::Span &Span();
            base::Span const &Span() const;

            /// @brief 数据项。
            /// @note 其中的有效字节如果不足 40 字节，需要填充字节到 40 字节。填充的字节的值为 0.
            /// @return
            base::profinet::DataItem DataItem() const;
            void SetDataItem(base::profinet::DataItem const &value);
        };
    } // namespace profinet
} // namespace base
