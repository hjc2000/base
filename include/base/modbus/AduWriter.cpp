#include "AduWriter.h" // IWYU pragma: keep
#include "base/string/ToHexString.h"

std::string base::modbus::AduWriter::SpanForSendingString() const
{
	std::string ret;
	base::ToHexStringOptions option{};
	option.with_0x_prefix = false;
	option.width = 2;

	bool is_first_loop = true;
	for (uint8_t b : SpanForSending())
	{
		if (is_first_loop)
		{
			is_first_loop = false;
		}
		else
		{
			ret += " ";
		}

		ret += base::ToHexString(b, option);
	}

	return ret;
}
