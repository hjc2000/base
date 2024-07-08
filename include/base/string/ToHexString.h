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

	/// @brief 将缓冲区中的每个字节变成 16 进制字符串，每个字节的字符串用逗号分隔，每
	/// 20 个字节一行。
	///
	/// @param buffer
	/// @param size
	/// @return
	std::string ToHexString(uint8_t *buffer, int32_t size);
}
