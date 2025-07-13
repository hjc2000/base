#pragma once
#include "AduWriter.h"
#include "base/stream/Span.h"
#include <cstdint>

namespace base
{
	namespace modbus
	{
		class ReadingRecordRequestWriter
		{
		private:
			base::modbus::AduWriter _adu_writer;

		public:
			ReadingRecordRequestWriter(base::Span const &span)
				: _adu_writer(span)
			{
			}

			///
			/// @brief 站号。
			///
			/// @return
			///
			uint8_t StationNumber() const
			{
				return _adu_writer.StationNumber();
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
			/// @brief 功能码。
			///
			/// @return
			///
			uint8_t FunctionCode() const
			{
				return 0x3;
			}

			///
			/// @brief 写入功能码。
			///
			///
			void WriteFunctionCode() const
			{
				_adu_writer.WriteFunctionCode(0x03);
			}

			///
			/// @brief 写入要读取记录的起始地址。
			///
			/// @param value
			///
			void WriteStartAddress(uint16_t value)
			{
				_adu_writer.WriteData(value);
			}

			///
			/// @brief 写入要读取的记录数量。
			///
			/// @param value
			///
			void WriteRecordCount(uint16_t value)
			{
				_adu_writer.WriteData(value);
			}

			///
			/// @brief 写入 CRC 校验。
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
