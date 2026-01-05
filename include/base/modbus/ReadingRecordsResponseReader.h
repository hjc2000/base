#pragma once
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
	/// @brief 读多个记录的响应帧读者。
	///
	///
	class ReadingRecordsResponseReader
	{
	private:
		base::modbus::AduReader _adu_reader;

	public:
		ReadingRecordsResponseReader(base::ReadOnlySpan const &span)
			: _adu_reader(span)
		{
			base::modbus::FunctionCode function_code = _adu_reader.FunctionCode();
			if (function_code != base::modbus::function_code::ReadRecords())
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
		/// @brief 数据字节数。
		///
		/// @return
		///
		uint8_t DataByteCount() const
		{
			return _adu_reader.DataSpan()[0];
		}

		///
		/// @brief 响应中发回来的数据。字节数为 DataByteCount().
		///
		/// @note 本读者类无法知道这里面的数据是什么含义和格式，所以只能是返回内存段。
		///
		/// @return
		///
		base::ReadOnlySpan DataSpan() const
		{
			base::ReadOnlySpan adu_data_span = _adu_reader.DataSpan();
			return adu_data_span[base::Range{1, adu_data_span.Size()}];
		}
	};

} // namespace base::modbus
