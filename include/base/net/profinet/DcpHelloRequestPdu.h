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

            base::Span &Span();
            base::Span const &Span() const;

            /// @brief DCP 头部
            /// @return
            base::profinet::DcpHeader Header() const;
            void SetHeader(base::profinet::DcpHeader const &value);

            base::profinet::NameOfStationBlockRes NameOfStationBlockRes() const;
            void SetNameOfStationBlockRes(base::profinet::NameOfStationBlockRes const &value);
        };
    } // namespace profinet
} // namespace base
