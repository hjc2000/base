#pragma once
#include <base/net/profinet/DcpHeader.h>

namespace base
{
    namespace profinet
    {
        class DcpHelloRequestPdu
        {
        private:
            base::Span _span;

        public:
            DcpHelloRequestPdu(base::Span const &span);

            base::profinet::DcpHeader Header() const;
        };
    } // namespace profinet
} // namespace base
