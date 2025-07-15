#pragma once

namespace base
{
	namespace modbus
	{
		enum class FunctionCode : uint8_t
		{
			///
			/// @brief 读取多个位。
			///
			///
			ReadBits = 0x1,

			///
			/// @brief 读取多个记录。
			///
			///
			ReadRecords = 0x3,

			///
			/// @brief 写入单个位。
			///
			///
			WriteSingleBit = 0x5,

			///
			/// @brief 写入多个位。
			///
			///
			WriteBits = 0xF,

			///
			/// @brief 写入多个记录。
			///
			///
			WriteRecords = 0x10,
		};

	} // namespace modbus
} // namespace base

constexpr bool operator==(base::modbus::FunctionCode lhs, uint8_t rhs)
{
	return static_cast<uint8_t>(lhs) == rhs;
}

constexpr bool operator==(uint8_t lhs, base::modbus::FunctionCode rhs)
{
	return static_cast<uint8_t>(rhs) == lhs;
}
