#pragma once
#include <cstdint>

namespace base::modbus
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

	///
	/// @brief 功能码枚举。
	///
	/// @note 放到独立的命名空间中进行枚举，方便用户和厂商进行扩展。如果放到类中就无法扩展了。
	///
	/// @note 使用 constexpr 函数而非 constexpr 变量是方便厂商和用户扩展时在里面进行一些计算。
	/// 此外，constexpr 函数在代码高亮中显示的颜色与命名空间的白色文字不同，方便区分。如果使用
	/// constexpr 变量，显示的也是白色，不利于区分。
	///
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

} // namespace base::modbus
