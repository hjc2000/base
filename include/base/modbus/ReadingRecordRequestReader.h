#pragma once
#include "AduReader.h"
#include "base/bit/AutoBitConverter.h"
#include "base/container/Range.h"
#include "base/stream/ReadOnlySpan.h"
#include <cstdint>

namespace base
{
	namespace modbus
	{
		class ReadingRecordRequestReader
		{
		private:
			base::modbus::AduReader _adu_reader;

		public:
			ReadingRecordRequestReader(base::ReadOnlySpan const &span)
				: _adu_reader(span)
			{
			}

			///
			/// @brief 站号。
			///
			/// @return
			///
			uint8_t StationNumber() const
			{
				return _adu_reader.StationNumber();
			}

			///
			/// @brief 功能码。
			///
			/// @return
			///
			uint8_t FunctionCode() const
			{
				return _adu_reader.FunctionCode();
			}

			///
			/// @brief 要读取的记录的起始地址。
			///
			/// @return
			///
			uint16_t StartAddress() const
			{
				base::ReadOnlySpan span = _adu_reader.DataSpan()[base::Range{0, 2}];
				uint16_t ret = base::big_endian_remote_converter.FromBytes<uint16_t>(span);
				return ret;
			}

			///
			/// @brief 要读取的记录的数量。
			///
			/// @return
			///
			uint16_t RecordCount() const
			{
				base::ReadOnlySpan span = _adu_reader.DataSpan()[base::Range{2, 4}];
				uint16_t ret = base::big_endian_remote_converter.FromBytes<uint16_t>(span);
				return ret;
			}

			///
			/// @brief 进行 CRC 校验。
			///
			/// @return true 表示 CRC 校验通过，false 表示 CRC 校验不通过。
			///
			bool CheckCrc() const
			{
				return _adu_reader.CheckCrc();
			}
		};

	} // namespace modbus
} // namespace base
