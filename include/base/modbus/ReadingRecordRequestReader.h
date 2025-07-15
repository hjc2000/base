#pragma once
#include "AduReader.h"
#include "base/bit/AutoBitConverter.h"
#include "base/container/Range.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/string/define.h"
#include <cstdint>
#include <stdexcept>

namespace base
{
	namespace modbus
	{
		///
		/// @brief 读记录的请求帧的读者。
		///
		///
		class ReadingRecordRequestReader
		{
		private:
			base::modbus::AduReader _adu_reader;

		public:
			ReadingRecordRequestReader(base::ReadOnlySpan const &span)
				: _adu_reader(span)
			{
				uint8_t function_code = _adu_reader.FunctionCode();
				if (function_code != 0x3)
				{
					throw std::runtime_error{CODE_POS_STR + "传入的帧不是请求读取记录的帧。"};
				}
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
		};

	} // namespace modbus
} // namespace base
