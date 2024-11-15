#pragma once
#include <base/net/profinet/ApduStatus.h>
#include <base/net/profinet/C_SDU.h>
#include <base/stream/Span.h>

namespace base
{
    namespace profinet
    {
        /// @brief 实时循环帧的协议数据单元。
        class RtcPdu
        {
        private:
            base::Span _span;

        public:
            RtcPdu() = default;
            RtcPdu(base::Span const &span);

            base::Span &Span();
            base::Span const &Span() const;

            base::profinet::C_SDU C_SDU() const;
            void Set_C_SDU(base::profinet::C_SDU const &value);

            base::profinet::ApduStatus ApduStatus() const;
            void SetApduStatus(base::profinet::ApduStatus const &value);
        };
    } // namespace profinet
} // namespace base
