#include "SentTelegram3Reader.h" // IWYU pragma: keep
#include "base/string/define.h"
#include <stdexcept>

base::profidrive::SentTelegram3Reader::SentTelegram3Reader(base::ReadOnlySpan const &span)
	: _span(span)
{
	if (span.Size() < 10)
	{
		throw std::invalid_argument{CODE_POS_STR + "内存段过小。"};
	}
}

base::profidrive::SentTelegram3 base::profidrive::SentTelegram3Reader::Read() const
{
	base::profidrive::SentTelegram3 ret{};
	ret.Set_STW1(STW1());
	ret.Set_NSOLL_B(NSOLL_B());
	ret.Set_STW2(STW2());
	ret.Set_G1_STW(G1_STW());
	return ret;
}
