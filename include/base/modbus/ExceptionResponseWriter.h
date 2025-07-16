#pragma once
#include "base/bit/bit.h"
#include "base/modbus/AduWriter.h"
#include <cstdint>

namespace base
{
	namespace modbus
	{
		class ExceptionResponseWriter
		{
		private:
			base::modbus::AduWriter _adu_writer;

		public:
			ExceptionResponseWriter(base::Span const &span)
				: _adu_writer(span)
			{
			}

			///
			/// @brief 写入站号。
			///
			/// @param value
			///
			void WriteStationNumber(uint8_t value) const
			{
				_adu_writer.WriteStationNumber(value);
			}

			///
			/// @brief 写入功能码。
			///
			/// @param value 正常的功能码，不是异常响应功能码。在响应哪个功能码的请求时出错了，
			/// 就直接写这个功能码就行了，本函数内部会自动写入异常响应功能码。
			///
			void WriteFunctionCode(uint8_t value) const
			{
				uint8_t exception_function_code = value;
				base::bit::WriteBit(exception_function_code, 7, 1);
				_adu_writer.WriteFunctionCode(exception_function_code);
			}
		};

	} // namespace modbus
} // namespace base
