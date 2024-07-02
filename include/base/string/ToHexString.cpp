#include "ToHexString.h"

std::string base::ToHexString(int8_t number)
{
	std::stringstream string_stream;
	string_stream << std::hex << static_cast<int>(number);
	return string_stream.str();
}

std::string base::ToHexString(uint8_t number)
{
	std::stringstream string_stream;
	string_stream << std::hex << static_cast<int>(number);
	return string_stream.str();
}

std::string base::ToHexString(int64_t number)
{
	std::stringstream string_stream;
	string_stream << std::hex << number;
	return string_stream.str();
}

std::string base::ToHexString(uint64_t number)
{
	std::stringstream string_stream;
	string_stream << std::hex << number;
	return string_stream.str();
}
