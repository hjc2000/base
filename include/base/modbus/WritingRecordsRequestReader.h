#pragma once
#include "base/bit/AutoBitConverter.h"
#include "base/container/Range.h"
#include "base/modbus/AduReader.h"
#include "base/modbus/FunctionCode.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/string/define.h"
#include <cstdint>
#include <stdexcept>

namespace base::modbus
{
	///
	/// @brief 写多个记录的请求帧读者。
	///
	class WritingRecordsRequestReader
	{
	private:
		base::modbus::AduReader _adu_reader;

	public:
		WritingRecordsRequestReader(base::ReadOnlySpan const &span)
			: _adu_reader(span)
		{
			base::modbus::FunctionCode function_code = _adu_reader.FunctionCode();
			if (function_code != base::modbus::function_code::WriteRecords())
			{
				throw std::runtime_error{CODE_POS_STR + "错误的功能码。"};
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
		/// @brief 要写入的数据的起始地址。
		///
		/// @return
		///
		uint16_t DataStartAddress() const
		{
			base::ReadOnlySpan span = _adu_reader.DataSpan()[base::Range{0, 2}];
			return base::big_endian_remote_converter.FromBytes<uint16_t>(span);
		}

		///
		/// @brief 要写入的记录数。
		///
		/// @note 一个记录 2 个字节。
		///
		/// @return
		///
		uint16_t RecordCount() const
		{
			base::ReadOnlySpan span = _adu_reader.DataSpan()[base::Range{2, 4}];
			return base::big_endian_remote_converter.FromBytes<uint16_t>(span);
		}

		///
		/// @brief 要写入的数据的字节数。
		///
		/// @return
		///
		uint8_t DataByteCount() const
		{
			return _adu_reader.DataSpan()[4];
		}

		///
		/// @brief 要写入的数据所在的内存段。
		///
		/// @return
		///
		base::ReadOnlySpan DataSpan() const
		{
			base::ReadOnlySpan adu_data_span = _adu_reader.DataSpan();
			return adu_data_span[base::Range{5, adu_data_span.Size()}];
		}
	};

} // namespace base::modbus
