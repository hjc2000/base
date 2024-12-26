#include "FidApdu.h"

base::profinet::FidApdu::FidApdu(base::Span const &span)
{
	_span = span;
}

base::Span const &base::profinet::FidApdu::Span() const
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
	/* 因为都是对内存段的引用，所以 Set 需要将整段内存拷贝而不能指示调用类的赋值运算符，这没有用，
	 * 赋值运算符改变的是指向内存段的指针。
	 */
	DcpHelloRequestPdu().Span().CopyFrom(value.Span());
}
