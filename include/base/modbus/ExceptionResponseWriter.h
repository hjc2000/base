#pragma once
#include "base/bit/bit.h"
#include "base/modbus/AduWriter.h"
#include "base/modbus/FunctionCode.h"
#include "ExceptionCode.h"
#include <bit>
#include <cstdint>

namespace base::modbus
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
		void WriteFunctionCode(base::modbus::FunctionCode const &value) const
		{
			uint8_t exception_function_code = value.Value();
			base::bit::WriteBit(exception_function_code, 7, 1);
			_adu_writer.WriteFunctionCode(base::modbus::FunctionCode{exception_function_code});
		}

		///
		/// @brief 写入异常代码。
		///
		/// @param value
		///
		void WriteExceptionCode(base::modbus::ExceptionCode const &value)
		{
			_adu_writer.WriteData(value.Value(), std::endian::big);
		}

		///
		/// @brief 写入 CRC.
		///
		///
		void WriteCrc() const
		{
			_adu_writer.WriteCrc();
		}

		///
		/// @brief 获取待发送的 span, 这里面包括了从站号到 CRC16 的所有数据，
		/// 可以直接全部发送出去。
		///
		/// @return
		///
		base::ReadOnlySpan SpanForSending() const
		{
			return _adu_writer.SpanForSending();
		}

		///
		/// @brief 将 SpanForSending 的每个字节转成 hex 字符串。这个字符串可以复制粘贴
		/// 到串口调试助手中发送出去。
		///
		/// @return
		///
		std::string SpanForSendingString() const
		{
			return _adu_writer.SpanForSendingString();
		}
	};

} // namespace base::modbus
