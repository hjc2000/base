#pragma once
#include <base/stream/Span.h>

namespace base
{
    /// @brief DCP 头部
    class DcpHeader
    {
    private:
        base::Span _span;

    public:
        DcpHeader(base::Span span);

        uint8_t ServiceId() const;
        void SetServiceId(uint8_t value);

        uint8_t ServiceType() const;
        void SetServiceType(uint8_t value);

        uint32_t Xid() const;
        void SetXid(uint32_t value);

        uint16_t ResponseDelayFactor() const;
        void SetResponseDelayFactor(uint16_t value);

        uint16_t DataLength() const;
        void SetDataLength(uint16_t value);
    };
} // namespace base
