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
	/// @brief 写入多个位的请求帧读者。
	///
	class WritingBitsRequestReader
	{
	private:
		base::modbus::AduReader _adu_reader;

	public:
		WritingBitsRequestReader(base::ReadOnlySpan const &span)
			: _adu_reader(span)
		{
			base::modbus::FunctionCode function_code = _adu_reader.FunctionCode();
			if (function_code != base::modbus::FunctionCode::Constants::WriteBits())
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

		///
		/// @brief 要写入的位数据被放在多少个字节里面。
		///
		/// @return
		///
		uint8_t ByteCount()
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
