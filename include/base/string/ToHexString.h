#pragma once
#include <sstream>
#include <stdint.h>
#include <string>

namespace base
{
	/// @brief 将数字转化为 16 进制的字符串
	/// @param number
	/// @return
	std::string ToHexString(int8_t number);
	std::string ToHexString(uint8_t number);

	std::string ToHexString(int16_t number);
	std::string ToHexString(uint16_t number);

	std::string ToHexString(int32_t number);
	std::string ToHexString(uint32_t number);

	std::string ToHexString(int64_t number);
	std::string ToHexString(uint64_t number);
}
