#pragma once
#include "base/modbus/AduWriter.h"
#include "base/modbus/FunctionCode.h"
#include <cstdint>

namespace base
{
	namespace modbus
	{
		class WritingRecordsResponseWriter
		{
		private:
			base::modbus::AduWriter _adu_writer;

		public:
			WritingRecordsResponseWriter(base::Span const &span)
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
				_adu_writer.WriteFunctionCode(static_cast<uint8_t>(base::modbus::FunctionCode::WriteRecords));
			}

			///
			/// @brief 写入刚才被请求写入的记录的起始地址。
			///
			/// @param value
			///
			void WriteStartAddress(uint16_t value)
			{
				_adu_writer.WriteData(value);
			}

			///
			/// @brief 写入刚才被请求写入的记录的数量。
			///
			/// @param value
			///
			void WriteRecordCount(uint16_t value)
			{
				_adu_writer.WriteData(value);
			}
		};

	} // namespace modbus
} // namespace base
