#pragma once
#include "base/container/Range.h"
#include "base/modbus/AduReader.h"
#include "base/modbus/FunctionCode.h"
#include "base/stream/ReadOnlySpan.h"
#include <cstdint>

namespace base::modbus
{
	///
	/// @brief 读取多个位数据的响应帧读者。
	///
	///
	class ReadingBitsResponseReader
	{
	private:
		base::modbus::AduReader _adu_reader;

	public:
		ReadingBitsResponseReader(base::ReadOnlySpan const &span)
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
		/// @brief 数据字节数。
		///
		/// @return
		///
		uint8_t ByteCount() const
		{
			return _adu_reader.DataSpan()[0];
		}

		///
		/// @brief 数据内存段。
		///
		/// @note 这里每个字节的一个位都是一个位数据。如果请求读取的位数据不是 8 的
		/// 整数倍，则最后一个字节会有一些高位是无效的，忽略它们就行了。
		///
		/// @return
		///
		base::ReadOnlySpan DataSpan() const
		{
			base::ReadOnlySpan adu_data_span = _adu_reader.DataSpan();
			return adu_data_span[base::Range{1, adu_data_span.Size()}];
		}
	};

} // namespace base::modbus
