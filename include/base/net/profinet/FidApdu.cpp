#include "FidApdu.h"

base::profinet::FidApdu::FidApdu(base::Span const &span)
{
    _span = span;
}

base::Span &base::profinet::FidApdu::Span()
{
    return _span;
}

base::profinet::FrameIdEnum base::profinet::FidApdu::FrameId() const
{
    return base::profinet::FrameIdEnum();
}

void base::profinet::FidApdu::SetFrameId(base::profinet::FrameIdEnum value)
{
}

base::profinet::DcpHelloRequestPdu base::profinet::FidApdu::DcpHelloRequestPdu() const
{
    return base::profinet::DcpHelloRequestPdu();
}

void base::profinet::FidApdu::SetDcpHelloRequestPdu(base::profinet::DcpHelloRequestPdu const &value)
{
}
