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
	/// @brief 写多个记录的响应帧读者。
	///
	///
	class WritingRecordsResponseReader
	{
	private:
		base::modbus::AduReader _adu_reader;

	public:
		WritingRecordsResponseReader(base::ReadOnlySpan const &span)
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
		/// @brief 起始地址。
		///
		/// @return
		///
		uint16_t StartAddress() const
		{
			base::ReadOnlySpan span = _adu_reader.DataSpan()[base::Range{0, 2}];
			return base::big_endian_remote_converter.FromBytes<uint16_t>(span);
		}

		///
		/// @brief 记录数。
		///
		/// @return
		///
		uint16_t RecordCount() const
		{
			base::ReadOnlySpan span = _adu_reader.DataSpan()[base::Range{2, 4}];
			return base::big_endian_remote_converter.FromBytes<uint16_t>(span);
		}
	};

} // namespace base::modbus
