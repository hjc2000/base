#pragma once
#include <base/stream/Span.h>

namespace base
{
    namespace profinet
    {
        class IPParameterType
        {
        public:
            IPParameterType() = default;
            IPParameterType(base::Span const &span);

            uint8_t IPOption() const;
            uint8_t SuboptionIPParameter() const;
        };
    } // namespace profinet
} // namespace base
