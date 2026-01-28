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
		/// @brief 要写入的数据的起始地址。
		///
		/// @return
		///
		uint16_t DataStartAddress()
		{
			uint16_t ret = _adu_reader.ReadData<uint16_t>(std::endian::big);
			return ret;
		}

		///
		/// @brief 要写入的记录数。
		///
		/// @note 一个记录 2 个字节。
		///
		/// @return
		///
		uint16_t RecordCount()
		{
			uint16_t ret = _adu_reader.ReadData<uint16_t>(std::endian::big);
			return ret;
		}

		///
		/// @brief 要写入的数据的字节数。
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
	};

} // namespace base::modbus
