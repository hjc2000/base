#pragma once
#include "base/modbus/AduWriter.h"
#include "base/modbus/FunctionCode.h"
#include "base/stream/Span.h"
#include <cstdint>

namespace base::modbus
{
	///
	/// @brief 写单个位的请求帧作者。
	///
	///
	class WritingSingleBitRequestWriter
	{
	private:
		base::modbus::AduWriter _adu_writer;

	public:
		WritingSingleBitRequestWriter(base::Span const &span)
			: _adu_writer(span)
		{
		}

		///
		/// @brief 写入站号。
		///
		/// @param value
		///
		void WriteStationNumber(uint8_t value) const
		{
			_adu_writer.WriteStationNumber(value);
		}

		///
		/// @brief 写入功能码。
		///
		///
		void WriteFunctionCode() const
		{
			_adu_writer.WriteFunctionCode(base::modbus::function_code::WriteSingleBit());
		}

		///
		/// @brief 写入要写入的位数据的地址。
		///
		/// @param value
		///
		void WriteAddress(uint16_t value)
		{
			_adu_writer.WriteData(value);
		}

		///
		/// @brief 写入要写入的位数据的值。
		///
		/// @param value
		///
		void WriteValue(bool value)
		{
			if (value)
			{
				_adu_writer.WriteData(static_cast<uint16_t>(0xFF00));
			}
			else
			{
				_adu_writer.WriteData(static_cast<uint16_t>(0x0000));
			}
		}

		///
		/// @brief 写入 CRC.
		///
		///
		void WriteCrc()
		{
			_adu_writer.WriteCrc();
		}

		///
		/// @brief 获取待发送的 span, 这里面包括了从站号到 CRC16 的所有数据，
		/// 可以直接全部发送出去。
		///
		/// @return
		///
		base::ReadOnlySpan SpanForSending() const
		{
			return _adu_writer.SpanForSending();
		}

		///
		/// @brief 将 SpanForSending 的每个字节转成 hex 字符串。这个字符串可以复制粘贴
		/// 到串口调试助手中发送出去。
		///
		/// @return
		///
		std::string SpanForSendingString() const
		{
			return _adu_writer.SpanForSendingString();
		}
	};

} // namespace base::modbus
