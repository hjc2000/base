#pragma once
#include "base/bit/AutoBitConverter.h"
#include "base/container/Range.h"
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
			if (function_code != base::modbus::function_code::WriteSingleBit())
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
		uint16_t Address() const
		{
			base::ReadOnlySpan span = _adu_reader.DataSpan()[base::Range{0, 2}];
			return base::big_endian_remote_converter.FromBytes<uint16_t>(span);
		}

		///
		/// @brief 要写入的位数据的值。
		///
		/// @return
		///
		bool Value() const
		{
			base::ReadOnlySpan span = _adu_reader.DataSpan()[base::Range{2, 4}];
			uint16_t word = base::big_endian_remote_converter.FromBytes<uint16_t>(span);

			if (word == 0xFF00)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	};

} // namespace base::modbus
