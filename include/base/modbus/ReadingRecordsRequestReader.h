#pragma once
#include "AduReader.h"
#include "base/bit/AutoBitConverter.h"
#include "base/container/Range.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/string/define.h"
#include "FunctionCode.h"
#include <cstdint>
#include <stdexcept>

namespace base::modbus
{
	///
	/// @brief 读多个记录的请求帧读者。
	///
	///
	class ReadingRecordsRequestReader
	{
	private:
		base::modbus::AduReader _adu_reader;

	public:
		ReadingRecordsRequestReader(base::ReadOnlySpan const &span)
			: _adu_reader(span)
		{
			base::modbus::FunctionCode function_code = _adu_reader.FunctionCode();
			if (function_code != base::modbus::function_code::ReadRecords())
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

} // namespace base::modbus
