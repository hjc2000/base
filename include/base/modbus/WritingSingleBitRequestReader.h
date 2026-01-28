#pragma once
#include "base/modbus/AduReader.h"
#include "base/modbus/FunctionCode.h"
#include "base/stream/ReadOnlySpan.h"
#include <cstdint>

namespace base::modbus
{
	///
	/// @brief 写单个位的请求帧读者。
	///
	class WritingSingleBitRequestReader
	{
	private:
		base::modbus::AduReader _adu_reader;

	public:
		WritingSingleBitRequestReader(base::ReadOnlySpan const &span)
			: _adu_reader(span)
		{
			base::modbus::FunctionCode function_code = _adu_reader.FunctionCode();
			if (function_code != base::modbus::FunctionCode::Constants::WriteSingleBit())
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
		/// @brief 要写入的位数据的地址。
		///
		/// @return
		///
		uint16_t Address()
		{
			uint16_t ret = _adu_reader.ReadData<uint16_t>(std::endian::big);
			return ret;
		}

		///
		/// @brief 要写入的位数据的值。
		///
		/// @return
		///
		bool Value()
		{
			uint16_t word = _adu_reader.ReadData<uint16_t>(std::endian::big);

			if (word == 0xFF00)
			{
				return true;
			}

			return false;
		}
	};

} // namespace base::modbus
