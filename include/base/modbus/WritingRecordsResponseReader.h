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
	/// @brief 写多个记录的响应帧读者。
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
			if (function_code != base::modbus::FunctionCode::Constants::WriteRecords())
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
		uint16_t StartAddress()
		{
			uint16_t ret = _adu_reader.ReadData<uint16_t>(std::endian::big);
			return ret;
		}

		///
		/// @brief 记录数。
		///
		/// @return
		///
		uint16_t RecordCount()
		{
			uint16_t ret = _adu_reader.ReadData<uint16_t>(std::endian::big);
			return ret;
		}

		///
		/// @brief 进行 CRC 校验。
		///
		/// @return true 表示 CRC 校验通过，false 表示 CRC 校验不通过。
		///
		bool CheckCrc()
		{
			return _adu_reader.CheckCrc();
		}
	};

} // namespace base::modbus
