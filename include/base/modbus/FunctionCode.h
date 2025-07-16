#pragma once
#include <cstdint>

namespace base
{
	namespace modbus
	{
		namespace function_code
		{
			///
			/// @brief 读取多个位。
			///
			///
			constexpr uint8_t ReadBits = 0x1;

			///
			/// @brief 读取多个记录。
			///
			///
			constexpr uint8_t ReadRecords = 0x3;

			///
			/// @brief 写入单个位。
			///
			///
			constexpr uint8_t WriteSingleBit = 0x5;

			///
			/// @brief 写入多个位。
			///
			///
			constexpr uint8_t WriteBits = 0xF;

			///
			/// @brief 写入多个记录。
			///
			///
			constexpr uint8_t WriteRecords = 0x10;

		} // namespace function_code
	} // namespace modbus
} // namespace base
