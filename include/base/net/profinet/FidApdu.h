#pragma once
#include <base/net/profinet/DcpHelloRequestPdu.h>
#include <base/net/profinet/enum/FrameIdEnum.h>
#include <base/stream/Span.h>

namespace base
{
    namespace profinet
    {
        class FidApdu
        {
        private:
            base::Span _span;

        public:
            FidApdu() = default;
            FidApdu(base::Span const &span);

            base::Span &Span();
            base::Span const &Span() const;

            base::profinet::FrameIdEnum FrameId() const;
            void SetFrameId(base::profinet::FrameIdEnum value);

#pragma region 以下 PDU 是互斥的
            base::profinet::DcpHelloRequestPdu DcpHelloRequestPdu() const;
            void SetDcpHelloRequestPdu(base::profinet::DcpHelloRequestPdu const &value);
#pragma endregion
        };
    } // namespace profinet
} // namespace base
