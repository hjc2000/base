#pragma once
#include "base/bit/AutoBitConverter.h"
#include "base/bit/bit.h"
#include "base/container/Range.h"
#include "base/modbus/AduReader.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/string/define.h"
#include <cstdint>
#include <stdexcept>

namespace base
{
	namespace modbus
	{
		class WritingRecordRequestReader
		{
		private:
			base::modbus::AduReader _adu_reader;

			static constexpr uint8_t FunctionCode()
			{
				return 0x10;
			}

			static constexpr uint8_t ExceptionFunctionCode()
			{
				uint8_t ret = FunctionCode();
				base::bit::WriteBit(ret, 7, 1);
				return ret;
			}

			void CheckFunctionCode() const
			{
				uint8_t function_code = _adu_reader.FunctionCode();
				if (function_code == FunctionCode())
				{
					return;
				}

				if (function_code == ExceptionFunctionCode())
				{
					return;
				}

				throw std::runtime_error{CODE_POS_STR + "错误的功能码。"};
			}

		public:
			WritingRecordRequestReader(base::ReadOnlySpan const &span)
				: _adu_reader(span)
			{
				CheckFunctionCode();
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
			/// @brief 要写入的数据的起始地址。
			///
			/// @return
			///
			uint16_t DataStartAddress() const
			{
				base::ReadOnlySpan span = _adu_reader.DataSpan()[base::Range{0, 2}];
				return base::big_endian_remote_converter.FromBytes<uint16_t>(span);
			}

			///
			/// @brief 要写入的记录数。
			///
			/// @note 一个记录 2 个字节。
			///
			/// @return
			///
			uint16_t RecordCount() const
			{
				base::ReadOnlySpan span = _adu_reader.DataSpan()[base::Range{2, 4}];
				return base::big_endian_remote_converter.FromBytes<uint16_t>(span);
			}

			///
			/// @brief 要写入的数据的字节数。
			///
			/// @return
			///
			uint8_t DataByteCount() const
			{
				return _adu_reader.DataSpan()[4];
			}

			///
			/// @brief 要写入的数据所在的内存段。
			///
			/// @return
			///
			base::ReadOnlySpan DataSpan() const
			{
				base::ReadOnlySpan adu_data_span = _adu_reader.DataSpan();
				return adu_data_span[base::Range{5, adu_data_span.Size()}];
			}
		};

	} // namespace modbus
} // namespace base
