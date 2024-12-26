#include "DcpHelloRequestPdu.h"

base::profinet::DcpHelloRequestPdu::DcpHelloRequestPdu(base::Span const &span)
{
	_span = span;
}

base::Span const &base::profinet::DcpHelloRequestPdu::Span() const
{
	return _span;
}

base::profinet::DcpHeader base::profinet::DcpHelloRequestPdu::Header() const
{
	return base::profinet::DcpHeader{};
}

void base::profinet::DcpHelloRequestPdu::SetHeader(base::profinet::DcpHeader const &value)
{
	Header().Span().CopyFrom(value.Span());
}

base::profinet::NameOfStationBlockRes base::profinet::DcpHelloRequestPdu::NameOfStationBlockRes() const
{
	return base::profinet::NameOfStationBlockRes();
}

void base::profinet::DcpHelloRequestPdu::SetNameOfStationBlockRes(base::profinet::NameOfStationBlockRes const &value)
{
	NameOfStationBlockRes().Span().CopyFrom(value.Span());
}
