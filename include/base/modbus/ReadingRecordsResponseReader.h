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
	/// @brief 读多个记录的响应帧读者。
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
			if (function_code != base::modbus::FunctionCode::Constants::ReadRecords())
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
		uint8_t DataByteCount()
		{
			uint8_t ret = _adu_reader.ReadData<uint8_t>(std::endian::big);
			return ret;
		}

		///
		/// @brief 读取载荷数据。
		///
		/// @param span
		///
		void ReadData(base::Span const &span)
		{
			_adu_reader.ReadData(span);
		}

		///
		/// @brief 读取载荷数据。
		///
		/// @param remote_endian
		///
		/// @return
		///
		template <typename ReturnType>
		ReturnType ReadData(std::endian remote_endian)
		{
			return _adu_reader.ReadData<ReturnType>(remote_endian);
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
