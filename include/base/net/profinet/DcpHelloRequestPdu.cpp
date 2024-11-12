#include "DcpHelloRequestPdu.h"

base::profinet::DcpHelloRequestPdu::DcpHelloRequestPdu(base::Span const &span)
{
    _span = span;
}

base::profinet::DcpHeader base::profinet::DcpHelloRequestPdu::Header() const
{
    return base::profinet::DcpHeader{_span};
}

uint16_t base::profinet::DcpHelloRequestPdu::BlockLength() const
{
    return 0;
}
