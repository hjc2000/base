#pragma once
#include <base/stream/Span.h>

namespace base
{
    namespace profinet
    {
        class DataItem
        {
        private:
            base::Span _span;

        public:
            DataItem() = default;
            DataItem(base::Span const &span);

            base::Span &Span();
            base::Span const &Span() const;

            uint8_t Iocs() const;
            void SetIocs(uint8_t value);
        };
    } // namespace profinet
} // namespace base
