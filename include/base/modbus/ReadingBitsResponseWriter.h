#pragma once
#include "base/modbus/AduWriter.h"
#include "base/modbus/FunctionCode.h"
#include "base/stream/Span.h"
#include <cstdint>

namespace base
{
	namespace modbus
	{
		///
		/// @brief 读取多个位数据的响应帧作者。
		///
		///
		class ReadingBitsResponseWriter
		{
		private:
			base::modbus::AduWriter _adu_writer;

		public:
			ReadingBitsResponseWriter(base::Span const &span)
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
			///
			void WriteFunctionCode() const
			{
				_adu_writer.WriteFunctionCode(base::modbus::FunctionCode::ReadBits());
			}

			///
			/// @brief 写入数据字节数。
			///
			/// @param value
			///
			void WriteByteCount(uint8_t value)
			{
				_adu_writer.WriteData(value);
			}

			///
			/// @brief 写入数据。
			///
			/// @param span
			///
			void WriteData(base::ReadOnlySpan const &span)
			{
				_adu_writer.WriteData(span);
			}

			///
			/// @brief 写入数据。
			///
			/// @param value
			///
			template <typename ValueType>
			void WriteData(ValueType value)
			{
				_adu_writer.WriteData(value);
			}

			///
			/// @brief 写入 CRC16.
			///
			///
			void WriteCrc()
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
		};

	} // namespace modbus
} // namespace base
