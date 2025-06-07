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
