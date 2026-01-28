#pragma once
#include "base/bit/AutoBitConverter.h"
#include "base/container/Range.h"
#include "base/modbus/FunctionCode.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include "base/string/define.h"
#include "base/string/ToHexString.h"
#include "ModbusCrc16.h"
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
		int32_t _data_writing_position = 0;

		base::Span DataSpan() const
		{
			return _span[base::Range{2, _span.Size() - 2}];
		}

	public:
		AduWriter(base::Span const &span)
		{
			if (span.Size() <= 4)
			{
				throw std::invalid_argument{CODE_POS_STR + "传入的 span 过小，无法写入 modbus 帧。"};
			}

			_span = span;
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
			base::Range range{
				_data_writing_position,
				_data_writing_position + span.Size(),
			};

			base::Span span_to_write = DataSpan()[range];
			span_to_write.CopyFrom(span);

			_data_writing_position += span_to_write.Size();
		}

		///
		/// @brief 写入数据。
		///
		/// @param value
		///
		template <typename ValueType>
		void WriteData(ValueType value, std::endian remote_endian)
		{
			base::Range range{
				_data_writing_position,
				_data_writing_position + static_cast<int64_t>(sizeof(ValueType)),
			};

			base::Span span_to_write = DataSpan()[range];

			base::AutoBitConverter conveter{remote_endian};
			conveter.GetBytes(value, span_to_write);

			_data_writing_position += span_to_write.Size();
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
			int32_t data_end_pos = 2 + _data_writing_position;

			base::ReadOnlySpan span_to_check = _span[base::Range{0, data_end_pos}];
			crc.Add(span_to_check);

			base::big_endian_remote_converter.GetBytes(crc.RegisterValue(),
													   _span[base::Range{data_end_pos, data_end_pos + 2}]);
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
			return _span[base::Range{0, 2 + _data_writing_position + 2}];
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
