#pragma once
#include "base/modbus/AduReader.h"
#include "base/modbus/FunctionCode.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/string/define.h"
#include <cstdint>
#include <stdexcept>

namespace base::modbus
{
	///
	/// @brief 读取多个位数据的请求帧读者。
	///
	class ReadingBitsRequestReader
	{
	private:
		base::modbus::AduReader _adu_reader;

	public:
		ReadingBitsRequestReader(base::ReadOnlySpan const &span)
			: _adu_reader(span)
		{
			base::modbus::FunctionCode function_code = _adu_reader.FunctionCode();
			if (function_code != base::modbus::function_code::ReadBits())
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
		/// @brief 要读取的位的起始地址。
		///
		/// @return
		///
		uint16_t StartAddress()
		{
			uint16_t ret = _adu_reader.ReadData<uint16_t>(std::endian::big);
			return ret;
		}

		///
		/// @brief 要读取的位的数量。
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
