#include "DcpHelloRequestPdu.h"

base::profinet::DcpHelloRequestPdu::DcpHelloRequestPdu(base::Span const &span)
{
    _span = span;
}

base::profinet::DcpHeader base::profinet::DcpHelloRequestPdu::Header() const
{
    return base::profinet::DcpHeader{};
}

base::profinet::NameOfStationBlockRes base::profinet::DcpHelloRequestPdu::NameOfStationBlockRes() const
{
    return base::profinet::NameOfStationBlockRes();
}
