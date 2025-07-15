#pragma once
#include "base/bit/bit.h"
#include "base/modbus/AduWriter.h"
#include <cstdint>

namespace base
{
	namespace modbus
	{
		///
		/// @brief 读记录的响应帧作者。
		///
		///
		class ReadingRecordResponseWriter
		{
		private:
			base::modbus::AduWriter _adu_writer;

			static constexpr uint8_t FunctionCode()
			{
				return 0x3;
			}

			static constexpr uint8_t ExceptionFunctionCode()
			{
				uint8_t ret = FunctionCode();
				base::bit::WriteBit(ret, 7, 1);
				return ret;
			}

		public:
			ReadingRecordResponseWriter(base::Span const &span)
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
				_adu_writer.WriteFunctionCode(FunctionCode());
			}

			///
			/// @brief 写入异常响应的功能码。
			///
			///
			void WriteExceptionFunctionCode()
			{
				_adu_writer.WriteFunctionCode(ExceptionFunctionCode());
			}

			///
			/// @brief 写入数据字节数。
			///
			/// @param value
			///
			void WriteDataByteCount(uint8_t value)
			{
				return _adu_writer.WriteData(value);
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
			void WriteData(ValueType value)
			{
				_adu_writer.WriteData(value);
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
		};

	} // namespace modbus
} // namespace base
