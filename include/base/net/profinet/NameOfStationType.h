#pragma once
#include <base/stream/Span.h>

namespace base
{
    namespace profinet
    {
        class NameOfStationType
        {
        public:
            NameOfStationType() = default;

            uint8_t DevicePropertiesOption() const;
        };
    } // namespace profinet
} // namespace base
