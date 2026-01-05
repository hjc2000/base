#pragma once
#include "base/modbus/AduReader.h"
#include "base/modbus/FunctionCode.h"
#include "base/stream/ReadOnlySpan.h"
#include <cstdint>

namespace base::modbus
{
	class WritingBitsResponseReader
	{
	private:
		base::modbus::AduReader _adu_reader;

	public:
		WritingBitsResponseReader(base::ReadOnlySpan const &span)
			: _adu_reader(span)
		{
			base::modbus::FunctionCode function_code = _adu_reader.FunctionCode();
			if (function_code != base::modbus::function_code::WriteBits())
			{
				throw std::runtime_error{CODE_POS_STR + "功能码错误。"};
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
		/// @brief 要写入的位数据的起始地址。
		///
		/// @return
		///
		uint16_t StartAddress() const
		{
			base::ReadOnlySpan span = _adu_reader.DataSpan()[base::Range{0, 2}];
			return base::big_endian_remote_converter.FromBytes<uint16_t>(span);
		}

		///
		/// @brief 要写入的位数据的个数。
		///
		/// @return
		///
		uint16_t BitCount() const
		{
			base::ReadOnlySpan span = _adu_reader.DataSpan()[base::Range{2, 4}];
			return base::big_endian_remote_converter.FromBytes<uint16_t>(span);
		}
	};

} // namespace base::modbus
