#pragma once
#include <cstdint>

namespace base
{
	namespace modbus
	{
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

		}

	} // namespace modbus
} // namespace base
