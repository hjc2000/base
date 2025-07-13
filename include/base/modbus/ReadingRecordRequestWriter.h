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
				_adu_writer.WriteFunctionCode(0x03);
			}

			uint8_t StationNumber() const
			{
				return _adu_writer.StationNumber();
			}

			void WriteStationNumber(uint8_t value) const
			{
				_adu_writer.WriteStationNumber(value);
			}

			void WriteStartAddress(uint16_t value)
			{
				_adu_writer.WriteData(value);
			}
		};

	} // namespace modbus
} // namespace base
