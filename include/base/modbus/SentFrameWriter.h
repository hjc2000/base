#pragma once
#include "base/bit/AutoBitConverter.h"
#include "base/container/Range.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include "base/string/define.h"
#include "ModbusCrc16.h"
#include <cstdint>
#include <stdexcept>

namespace base
{
	namespace modbus
	{
		class SentFrameWriter
		{
		private:
			base::Span _span{};
			int32_t _data_length = 0;

		public:
			SentFrameWriter(base::Span const &span)
			{
				if (span.Size() <= 4)
				{
					throw std::invalid_argument{CODE_POS_STR + "传入的 span 过小，无法写入 modbus 帧。"};
				}

				_span = span;
			}

			///
			/// @brief 站号。
			///
			/// @return
			///
			uint8_t StationNumber() const
			{
				return _span[0];
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
			/// @brief 功能码。
			///
			/// @return
			///
			uint8_t FunctionCode() const
			{
				return _span[1];
			}

			///
			/// @brief 写入功能码。
			///
			/// @param value
			///
			void WriteFunctionCode(uint8_t value) const
			{
				_span[1] = value;
			}

			///
			/// @brief 写入数据。
			///
			/// @param span
			///
			void WriteData(base::ReadOnlySpan const &span)
			{
				int32_t write_pos = 2 + _data_length;
				base::Span to_write = _span[base::Range{write_pos, write_pos + span.Size()}];
				to_write.CopyFrom(span);
				_data_length += span.Size();
			}

			///
			/// @brief 清空数据。
			///
			///
			void ClearData()
			{
				_data_length = 0;
			}

			///
			/// @brief 写入 CRC16.
			///
			///
			void WriteCrc()
			{
				base::modbus::ModbusCrc16 crc{};
				int32_t data_end_pos = 2 + _data_length;
				base::ReadOnlySpan to_check = _span[base::Range{0, data_end_pos}];
				crc.Add(to_check);

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
				// 1 个字节的站好 + 1 个字节的功能码 + 数据 + 2 个字节的 CRC16.
				return _span[base::Range{0, 2 + _data_length + 2}];
			}
		};

	} // namespace modbus
} // namespace base
