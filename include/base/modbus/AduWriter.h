#pragma once
#include "base/container/Range.h"
#include "base/modbus/FunctionCode.h"
#include "base/modbus/ModbusCrc16.h"
#include "base/stream/PayloadWriter.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include "base/string/define.h"
#include "base/string/ToHexString.h"
#include <bit>
#include <cstdint>
#include <stdexcept>
#include <string>

namespace base::modbus
{
	class AduWriter
	{
	private:
		base::Span _span{};
		base::PayloadWriter _payload_writer;

	public:
		AduWriter(base::Span const &span)
			: _span{span},
			  _payload_writer{_span[base::Range{2, _span.Size()}]}
		{
			if (span.Size() <= 4)
			{
				throw std::invalid_argument{CODE_POS_STR + "传入的 span 过小，无法写入 modbus 帧。"};
			}
		}

		///
		/// @brief 写入站号。
		///
		/// @param value
		///
		void WriteStationNumber(uint8_t value) const
		{
			_span[0] = value;
		}

		///
		/// @brief 写入功能码。
		///
		/// @param value
		///
		void WriteFunctionCode(base::modbus::FunctionCode const &value) const
		{
			_span[1] = value.Value();
		}

		///
		/// @brief 写入数据。
		///
		/// @param span
		///
		void WriteData(base::ReadOnlySpan const &span)
		{
			_payload_writer.WritePayload(span);
		}

		///
		/// @brief 写入数据。
		///
		/// @param value
		///
		template <typename ValueType>
		void WriteData(ValueType value, std::endian remote_endian)
		{
			_payload_writer.WritePayload(value, remote_endian);
		}

		///
		/// @brief 写入 CRC16.
		///
		void WriteCrc()
		{
			base::modbus::ModbusCrc16 crc{};

			// 数据的最后一个字节的下一个字节的索引是
			// 		2 + _data_length
			// 加 2 是因为有 2 字节的头部。
			int32_t data_end = 2 + _payload_writer.Position();

			base::ReadOnlySpan span_to_check = _span[base::Range{0, data_end}];
			crc.Add(span_to_check);

			_payload_writer.WritePayload(crc.RegisterValue(), std::endian::big);
		}

		///
		/// @brief 获取待发送的 span, 这里面包括了从站号到 CRC16 的所有数据，
		/// 可以直接全部发送出去。
		///
		/// @return
		///
		base::ReadOnlySpan SpanForSending() const
		{
			// 1 个字节的站号 + 1 个字节的功能码 + 数据 + 2 个字节的 CRC16.
			return _span[base::Range{0, 2 + _payload_writer.Position()}];
		}

		///
		/// @brief 将 SpanForSending 的每个字节转成 hex 字符串。这个字符串可以复制粘贴
		/// 到串口调试助手中发送出去。
		///
		/// @return
		///
		std::string SpanForSendingString() const
		{
			std::string ret;
			base::ToHexStringOptions option{};
			option.with_0x_prefix = false;
			option.width = 2;

			bool is_first_loop = true;

			for (uint8_t b : SpanForSending())
			{
				if (is_first_loop)
				{
					is_first_loop = false;
				}
				else
				{
					ret += " ";
				}

				ret += base::ToHexString(b, option);
			}

			return ret;
		}
	};

} // namespace base::modbus
