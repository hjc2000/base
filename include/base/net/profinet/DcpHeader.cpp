#include "DcpHeader.h"

base::DcpHeader::DcpHeader(base::Span span)
{
    _span = span;
}

uint8_t base::DcpHeader::ServiceId() const
{
    return 0;
}

void base::DcpHeader::SetServiceId(uint8_t value)
{
}

uint8_t base::DcpHeader::ServiceType() const
{
    return 0;
}

void base::DcpHeader::SetServiceType(uint8_t value)
{
}

uint32_t base::DcpHeader::Xid() const
{
    return 0;
}

void base::DcpHeader::SetXid(uint32_t value)
{
}

uint16_t base::DcpHeader::ResponseDelayFactor() const
{
    return 0;
}

void base::DcpHeader::SetResponseDelayFactor(uint16_t value)
{
}

uint16_t base::DcpHeader::DataLength() const
{
    return 0;
}

void base::DcpHeader::SetDataLength(uint16_t value)
{
}
