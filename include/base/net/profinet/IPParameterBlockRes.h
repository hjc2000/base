#pragma once
#include <base/net/profinet/IPParameterType.h>
#include <base/net/profinet/IPParameterValue.h>
#include <base/stream/Span.h>

namespace base
{
    namespace profinet
    {
        class IPParameterBlockRes
        {
        public:
            IPParameterType Type() const;

            /// @brief DCP Block Length
            /// @return
            uint16_t BlockLength() const;

            /// @brief DCP Block Info
            /// @return
            uint16_t BlockInfo() const;

            IPParameterValue Value() const;
        };
    } // namespace profinet
} // namespace base
