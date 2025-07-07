#include "SentTelegram3Writer.h"

base::profidrive::SentTelegram3Writer::SentTelegram3Writer(base::Span const &span)
	: _span(span)
{
	if (span.Size() < 10)
	{
		throw std::invalid_argument{CODE_POS_STR + "内存段过小。"};
	}
}

void base::profidrive::SentTelegram3Writer::Write(base::profidrive::SentTelegram3 const &value)
{
	Write_STW1(value.STW1());
	Write_NSOLL_B(value.NSOLL_B());
	Write_STW2(value.STW2());
	Write_G1_STW(value.G1_STW());
}
