#pragma once
#include <cstdint>

namespace base::modbus
{
	///
	/// @brief 异常代码。
	///
	class ExceptionCode
	{
	private:
		uint8_t _value = 0;

	public:
		constexpr ExceptionCode() = default;

		constexpr explicit ExceptionCode(uint8_t value)
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

		constexpr bool operator==(ExceptionCode const &other) const
		{
			return _value == other._value;
		}
	};

	namespace exception_code
	{
		///
		/// @brief 非法功能。
		///
		/// @note 功能码指定的功能不被支持。
		///
		/// @return
		///
		constexpr base::modbus::ExceptionCode IllegalFunction()
		{
			return base::modbus::ExceptionCode{0x01};
		}

		///
		/// @brief 非法数据地址。
		///
		/// @note 这个地址没有数据可供写入或读取。或者地址的对齐不符合要求。
		///
		/// @return
		///
		constexpr base::modbus::ExceptionCode IllegalDataAddress()
		{
			return base::modbus::ExceptionCode{0x02};
		}

		///
		/// @brief 非法数据值。
		///
		/// @note 可能是如下情况
		/// 	@li 写入的数据值超出合法范围。
		/// 	@li 帧格式本身的错误。例如指定的数据字节数与记录数不匹配。
		///
		/// @return
		///
		constexpr base::modbus::ExceptionCode IllegalDataValue()
		{
			return base::modbus::ExceptionCode{0x03};
		}

	} // namespace exception_code

} // namespace base::modbus
