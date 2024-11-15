#include "RtcPdu.h"

base::profinet::RtcPdu::RtcPdu(base::Span const &span)
{
    _span = span;
}

base::Span &base::profinet::RtcPdu::Span()
{
    return _span;
}

base::Span const &base::profinet::RtcPdu::Span() const
{
    return _span;
}

base::profinet::C_SDU base::profinet::RtcPdu::C_SDU() const
{
    return base::profinet::C_SDU();
}

void base::profinet::RtcPdu::Set_C_SDU(base::profinet::C_SDU const &value)
{
    C_SDU().Span().CopyFrom(value.Span());
}

base::profinet::ApduStatus base::profinet::RtcPdu::ApduStatus() const
{
    return base::profinet::ApduStatus();
}

void base::profinet::RtcPdu::SetApduStatus(base::profinet::ApduStatus const &value)
{
    ApduStatus().Span().CopyFrom(value.Span());
}
