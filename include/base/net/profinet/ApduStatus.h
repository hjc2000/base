#pragma once
#include <base/stream/Span.h>

namespace base
{
    namespace profinet
    {
        /// @brief 应用层协议数据单元的状态。
        class ApduStatus
        {
        private:
            base::Span _span;

        public:
            ApduStatus() = default;
            ApduStatus(base::Span const &span);

            base::Span &Span();
            base::Span const &Span() const;
        };
    } // namespace profinet
} // namespace base
