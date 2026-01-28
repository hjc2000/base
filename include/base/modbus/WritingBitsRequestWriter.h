#pragma once
#include "base/modbus/AduWriter.h"
#include "FunctionCode.h"
#include <cstdint>

namespace base::modbus
{
	///
	/// @brief 写入多个位的请求帧作者。
	///
	class WritingBitsRequestWriter
	{
	private:
		base::modbus::AduWriter _adu_writer;

	public:
		WritingBitsRequestWriter(base::Span const &span)
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
			_adu_writer.WriteFunctionCode(base::modbus::FunctionCode::Constants::WriteBits());
		}

		///
		/// @brief 写入要写入的位数据的起始地址。
		///
		/// @param value
		///
		void WriteStartAddress(uint16_t value)
		{
			_adu_writer.WriteData(value, std::endian::big);
		}

		///
		/// @brief 写入要写入的位数据的个数。
		///
		/// @param value
		///
		void WriteBitCount(uint16_t value)
		{
			_adu_writer.WriteData(value, std::endian::big);
		}

		///
		/// @brief 写入：要写入的位数据被放在多少个字节里面。
		///
		/// @param value
		///
		void WriteByteCount(uint8_t value)
		{
			_adu_writer.WriteData(value, std::endian::big);
		}

		///
		/// @brief 写入数据。
		///
		/// @param span
		///
		void WriteData(base::ReadOnlySpan const &span)
		{
			_adu_writer.WriteData(span);
		}

		///
		/// @brief 写入数据。
		///
		/// @param value
		///
		template <typename ValueType>
		void WriteData(ValueType value, std::endian remote_endian)
		{
			_adu_writer.WriteData(value, remote_endian);
		}

		///
		/// @brief 写入校验和。
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
