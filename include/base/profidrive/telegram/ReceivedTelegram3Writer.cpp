#include "ReceivedTelegram3Writer.h"
#include "base/string/define.h"
#include <stdexcept>

base::profidrive::ReceivedTelegram3Writer::ReceivedTelegram3Writer(base::Span const &span)
	: _span(span)
{
	if (span.Size() < 18)
	{
		throw std::invalid_argument{CODE_POS_STR + "内存段过小。"};
	}
}

void base::profidrive::ReceivedTelegram3Writer::Write(base::profidrive::ReceivedTelegram3 const &value)
{
	Write_ZSW1(value.ZSW1());
	Write_NIST_B(value.NIST_B());
	Write_ZSW2(value.ZSW2());
	Write_G1_ZSW(value.G1_ZSW());
	Write_G1_XIST1(value.G1_XIST1());
	Write_G1_XIST2(value.G1_XIST2());
}
