#pragma once
#include "base/container/Range.h"
#include "base/modbus/FunctionCode.h"
#include "base/stream/PayloadReader.h"
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
		base::PayloadReader _payload_reader;

	public:
		///
		/// @brief
		///
		/// @param span 传进来的内存段必须以站号开始，以 CRC16 结尾，不得在末尾含有
		/// 无效字节。传进来的整个内存段都是有效数据。
		///
		AduReader(base::ReadOnlySpan const &span)
			: _span{span},
			  _payload_reader{_span[base::Range{2, _span.Size()}]}
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
		/// @brief 读取载荷数据。
		///
		/// @param span
		///
		void ReadData(base::Span const &span)
		{
			_payload_reader.ReadPayload(span);
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
			return _payload_reader.ReadPayload<ReturnType>(remote_endian);
		}

		///
		/// @brief 进行 CRC 校验。
		///
		/// @return true 表示 CRC 校验通过，false 表示 CRC 校验不通过。
		///
		bool CheckCrc()
		{
			base::modbus::ModbusCrc16 crc{};
			crc.Add(_span[base::Range{0, 2 + _payload_reader.Position()}]);

			uint16_t received_crc_value = _payload_reader.ReadPayload<uint16_t>(std::endian::big);

			return crc.RegisterValue() == received_crc_value;
		}
	};

} // namespace base::modbus
