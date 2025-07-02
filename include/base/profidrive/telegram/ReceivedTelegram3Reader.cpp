#include "ReceivedTelegram3Reader.h"
#include "base/string/define.h"
#include <stdexcept>

base::profidrive::ReceivedTelegram3Reader::ReceivedTelegram3Reader(base::ReadOnlySpan const &span)
	: _span(span)
{
	if (span.Size() < 18)
	{
		throw std::invalid_argument{CODE_POS_STR + "内存段过小。"};
	}
}

base::profidrive::ReceivedTelegram3 base::profidrive::ReceivedTelegram3Reader::Read() const
{
	base::profidrive::ReceivedTelegram3 ret{};
	ret.Set_ZSW1(ZSW1());
	ret.Set_NIST_B(NIST_B());
	ret.Set_ZSW2(ZSW2());
	ret.Set_G1_ZSW(G1_ZSW());
	ret.Set_G1_XIST1(G1_XIST1());
	ret.Set_G1_XIST2(G1_XIST2());
	return ret;
}
