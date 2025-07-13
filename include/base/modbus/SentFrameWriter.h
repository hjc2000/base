#pragma once
#include "base/bit/bit_converte.h"
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
			int32_t _data_length = 2;

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

			void WriteData(base::ReadOnlySpan const &span)
			{
				base::Span to_write = _span[base::Range{2 + _data_length, span.Size()}];
				to_write.CopyFrom(span);
				_data_length += span.Size();
			}

			void ClearData()
			{
				_data_length = 0;
			}

			void WriteCrc()
			{
				base::modbus::ModbusCrc16 crc{};
				base::ReadOnlySpan to_check = _span[base::Range{0, 2 + _data_length}];
				crc.Add(to_check);

				base::bit_converte::GetBytes(crc.RegisterValue(),
											 _span[base::Range{2 + _data_length, 2 + _data_length + 2}]);
			}

			base::ReadOnlySpan SpanForSending() const
			{
				return _span[base::Range{0, 2 + _data_length + 2}];
			}
		};

	} // namespace modbus
} // namespace base
