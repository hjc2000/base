#pragma once
#include "base/modbus/AduWriter.h"
#include <cstdint>

namespace base
{
	namespace modbus
	{
		///
		/// @brief 读记录的响应帧作者。
		///
		///
		class ReadingRecordResponseWriter
		{
		private:
			base::modbus::AduWriter _adu_writer;

		public:
			ReadingRecordResponseWriter(base::Span const &span)
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
				return 0x03;
			}

			///
			/// @brief 写入功能码。
			///
			///
			void WriteFunctionCode() const
			{
				_adu_writer.WriteFunctionCode(0x03);
			}
		};

	} // namespace modbus
} // namespace base
