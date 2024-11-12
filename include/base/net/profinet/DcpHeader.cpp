#include "DcpHeader.h"

base::profinet::DcpHeader::DcpHeader(base::Span const &span)
{
    _span = span;
}

base::profinet::ServiceIdEnum base::profinet::DcpHeader::ServiceId() const
{
    return base::profinet::ServiceIdEnum::Get;
}

void base::profinet::DcpHeader::SetServiceId(base::profinet::ServiceIdEnum value)
{
}

base::profinet::ServiceTypeEnum base::profinet::DcpHeader::ServiceType() const
{
    return ServiceTypeEnum();
}

void base::profinet::DcpHeader::SetServiceType(ServiceTypeEnum value)
{
}

uint32_t base::profinet::DcpHeader::Xid() const
{
    return 0;
}

void base::profinet::DcpHeader::SetXid(uint32_t value)
{
}

uint16_t base::profinet::DcpHeader::ResponseDelayFactor() const
{
    return 0;
}

void base::profinet::DcpHeader::SetResponseDelayFactor(uint16_t value)
{
}

uint16_t base::profinet::DcpHeader::DataLength() const
{
    return 0;
}

void base::profinet::DcpHeader::SetDataLength(uint16_t value)
{
}
