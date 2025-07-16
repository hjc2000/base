#pragma once
#include "AduWriter.h"
#include "base/modbus/FunctionCode.h"
#include "base/stream/Span.h"
#include <cstdint>

namespace base
{
	namespace modbus
	{
		class WritingBitsResponseWriter
		{
		private:
			base::modbus::AduWriter _adu_writer;

		public:
			WritingBitsResponseWriter(base::Span const &span)
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
				_adu_writer.WriteFunctionCode(base::modbus::function_code::WriteBits);
			}

			///
			/// @brief 写入起始地址。
			///
			/// @param value
			///
			void WriteStartAddress(uint16_t value)
			{
				_adu_writer.WriteData(value);
			}

			///
			/// @brief 写入位数据个数。
			///
			/// @param value
			///
			void WriteBitCount(uint16_t value)
			{
				_adu_writer.WriteData(value);
			}

			///
			/// @brief 写入 CRC.
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
