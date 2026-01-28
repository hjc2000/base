#pragma once
#include "base/bit/bit.h"
#include "base/modbus/AduReader.h"
#include "base/modbus/ExceptionCode.h"
#include "base/modbus/FunctionCode.h"
#include "base/string/define.h"
#include <cstdint>
#include <stdexcept>

namespace base::modbus
{
	///
	/// @brief 异常响应报文读者。
	///
	class ExceptionResponseReader
	{
	private:
		base::modbus::AduReader _adu_reader;

	public:
		ExceptionResponseReader(base::ReadOnlySpan const &span)
			: _adu_reader(span)
		{
			base::modbus::FunctionCode function_code = _adu_reader.FunctionCode();
			if (!base::bit::ReadBit(function_code.Value(), 7))
			{
				throw std::runtime_error{CODE_POS_STR + "不是异常响应报文。"};
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
		/// @brief 功能码。
		///
		/// @return 已经将异常响应功能码还原为正常功能码，即将最高位的 1 复位为 0.
		///
		base::modbus::FunctionCode FunctionCode() const
		{
			base::modbus::FunctionCode function_code = _adu_reader.FunctionCode();
			uint8_t value = function_code.Value();
			base::bit::WriteBit(value, 7, 0);
			return base::modbus::FunctionCode{value};
		}

		///
		/// @brief 异常代码。
		///
		/// @return
		///
		base::modbus::ExceptionCode ExceptionCode()
		{
			uint8_t value = _adu_reader.ReadData<uint8_t>(std::endian::big);
			return base::modbus::ExceptionCode{value};
		}
	};

} // namespace base::modbus
