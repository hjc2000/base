#pragma once
#include <cstdint>

namespace base
{
	namespace modbus
	{
		class FunctionCode
		{
		private:
			uint8_t _value{};

		public:
			constexpr FunctionCode() = default;

			constexpr explicit FunctionCode(uint8_t value)
				: _value(value)
			{
			}

			constexpr uint8_t Value() const
			{
				return _value;
			}

			constexpr explicit operator uint8_t() const
			{
				return _value;
			}

			constexpr bool operator==(FunctionCode const &other) const
			{
				return _value == other._value;
			}
		};

		namespace function_code
		{
			///
			/// @brief 读取多个位。
			///
			///
			constexpr base::modbus::FunctionCode ReadBits()
			{
				return base::modbus::FunctionCode{0x1};
			}

			///
			/// @brief 读取多个记录。
			///
			///
			constexpr base::modbus::FunctionCode ReadRecords()
			{
				return base::modbus::FunctionCode{0x3};
			}

			///
			/// @brief 写入单个位。
			///
			///
			constexpr base::modbus::FunctionCode WriteSingleBit()
			{
				return base::modbus::FunctionCode{0x5};
			}

			///
			/// @brief 写入多个位。
			///
			///
			constexpr base::modbus::FunctionCode WriteBits()
			{
				return base::modbus::FunctionCode{0xF};
			}

			///
			/// @brief 写入多个记录。
			///
			///
			constexpr base::modbus::FunctionCode WriteRecords()
			{
				return base::modbus::FunctionCode{0x10};
			}

		} // namespace function_code

	} // namespace modbus
} // namespace base
