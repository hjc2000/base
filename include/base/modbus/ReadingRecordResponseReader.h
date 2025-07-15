#pragma once
#include "base/bit/bit.h"
#include "base/modbus/AduReader.h"
#include "base/string/define.h"
#include <cstdint>
#include <stdexcept>

namespace base
{
	namespace modbus
	{
		///
		/// @brief 读记录的响应帧读者。
		///
		///
		class ReadingRecordResponseReader
		{
		private:
			base::modbus::AduReader _adu_reader;

			static constexpr uint8_t ExceptionFunctionCode()
			{
				uint8_t ret = static_cast<uint8_t>(0x3);
				base::bit::WriteBit(ret, 7, 1);
				return ret;
			}

			void CheckFunctionCode() const
			{
				uint8_t function_code = _adu_reader.FunctionCode();
				if (function_code == 0x3)
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
			ReadingRecordResponseReader(base::ReadOnlySpan const &span)
				: _adu_reader(span)
			{
				CheckFunctionCode();
			}
		};

	} // namespace modbus
} // namespace base
