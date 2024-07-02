#pragma once
#include <sstream>
#include <stdint.h>
#include <string>

namespace base
{
	std::string ToHexString(int8_t number);
	std::string ToHexString(uint8_t number);

	std::string ToHexString(int64_t number);
	std::string ToHexString(uint64_t number);
}
