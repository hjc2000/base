#pragma once
#include "base/bit/AutoBitConverter.h"
#include "base/container/Range.h"
#include "base/modbus/FunctionCode.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/string/define.h"
#include "ModbusCrc16.h"
#include <cstdint>
#include <stdexcept>

namespace base::modbus
{
	class AduReader
	{
	private:
		base::ReadOnlySpan _span{};
		int64_t _data_reading_position = 0;

		///
		/// @brief 数据内存段。
		///
		/// @return
		///
		base::ReadOnlySpan DataSpan() const
		{
			return _span[base::Range{2, _span.Size() - 2}];
		}

		///
		/// @brief CRC 校验数据的内存段。
		///
		/// @return
		///
		base::ReadOnlySpan CrcSpan() const
		{
			return _span[base::Range{_span.Size() - 2, _span.Size()}];
		}

		///
		/// @brief CRC 校验值。
		///
		/// @return
		///
		uint16_t Crc() const
		{
			return base::big_endian_remote_converter.FromBytes<uint16_t>(CrcSpan());
		}

	public:
		///
		/// @brief
		///
		/// @param span 传进来的内存段必须以站号开始，以 CRC16 结尾，不得在末尾含有
		/// 无效字节。传进来的整个内存段都是有效数据。
		///
		AduReader(base::ReadOnlySpan const &span)
			: _span{span}
		{
			if (span.Size() < 4)
			{
				throw std::invalid_argument{CODE_POS_STR + "传入的 span 过小，不可能装下 modbus 帧，无法读取。"};
			}
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
		/// @brief 功能码。
		///
		/// @return
		///
		base::modbus::FunctionCode FunctionCode() const
		{
			return base::modbus::FunctionCode{_span[1]};
		}

		///
		/// @brief 重置数据读取指针。
		///
		void ResetDataReadingPosition()
		{
			_data_reading_position = 0;
		}

		///
		/// @brief 读取载荷数据。
		///
		/// @param span
		///
		void ReadData(base::Span const &span)
		{
			base::Range range_to_read{
				_data_reading_position,
				_data_reading_position + span.Size(),
			};

			base::ReadOnlySpan span_to_read = DataSpan()[range_to_read];
			span.CopyFrom(span_to_read);
			_data_reading_position += span_to_read.Size();
		}

		///
		/// @brief 读取载荷数据。
		///
		/// @param remote_endian
		///
		/// @return
		///
		template <typename ReturnType>
		ReturnType ReadData(std::endian remote_endian)
		{
			base::Range range_to_read{
				_data_reading_position,
				_data_reading_position + static_cast<int64_t>(sizeof(ReturnType)),
			};

			base::ReadOnlySpan span_to_read = DataSpan()[range_to_read];

			base::AutoBitConverter conveter{remote_endian};
			ReturnType ret = conveter.FromBytes<ReturnType>(span_to_read);

			_data_reading_position += span_to_read.Size();
			return ret;
		}

		///
		/// @brief 进行 CRC 校验。
		///
		/// @return true 表示 CRC 校验通过，false 表示 CRC 校验不通过。
		///
		bool CheckCrc() const
		{
			base::modbus::ModbusCrc16 crc{};
			crc.Add(_span[base::Range{0, _span.Size() - 2}]);
			return crc.RegisterValue() == Crc();
		}
	};

} // namespace base::modbus
