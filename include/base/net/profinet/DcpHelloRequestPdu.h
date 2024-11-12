#pragma once
#include <base/net/profinet/DcpHeader.h>
#include <base/net/profinet/NameOfStationBlockRes.h>

namespace base
{
    namespace profinet
    {
        class DcpHelloRequestPdu
        {
        private:
            base::Span _span;

        public:
            DcpHelloRequestPdu() = default;
            DcpHelloRequestPdu(base::Span const &span);

            /// @brief DCP 头部
            /// @return
            base::profinet::DcpHeader Header() const;

            base::profinet::NameOfStationBlockRes NameOfStationBlockRes() const;
        };
    } // namespace profinet
} // namespace base
