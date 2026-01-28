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
		uint16_t StartAddress()
		{
			uint16_t ret = _adu_reader.ReadData<uint16_t>(std::endian::big);
			return ret;
		}

		///
		/// @brief 要写入的位数据的个数。
		///
		/// @return
		///
		uint16_t BitCount()
		{
			uint16_t ret = _adu_reader.ReadData<uint16_t>(std::endian::big);
			return ret;
		}
	};

} // namespace base::modbus
