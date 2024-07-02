#include "ToHexString.h"

std::string base::ToHexString(int8_t number)
{
	return ToHexString(static_cast<uint64_t>(number));
}

std::string base::ToHexString(uint8_t number)
{
	return ToHexString(static_cast<uint64_t>(number));
}

std::string base::ToHexString(int16_t number)
{
	return ToHexString(static_cast<uint64_t>(number));
}

std::string base::ToHexString(uint16_t number)
{
	return ToHexString(static_cast<uint64_t>(number));
}

std::string base::ToHexString(int32_t number)
{
	return ToHexString(static_cast<uint64_t>(number));
}

std::string base::ToHexString(uint32_t number)
{
	return ToHexString(static_cast<uint64_t>(number));
}

std::string base::ToHexString(int64_t number)
{
	return ToHexString(static_cast<uint64_t>(number));
}

std::string base::ToHexString(uint64_t number)
{
	std::stringstream string_stream;
	string_stream << "0x" << std::hex << number;
	return string_stream.str();
}
