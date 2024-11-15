#pragma once
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
        };
    } // namespace profinet
} // namespace base
