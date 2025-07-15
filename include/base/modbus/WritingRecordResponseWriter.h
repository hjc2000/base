#pragma once
#include "base/bit/bit.h"
#include "base/modbus/AduWriter.h"

namespace base
{
	namespace modbus
	{
		class WritingRecordResponseWriter
		{
		private:
			base::modbus::AduWriter _adu_writer;

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

		public:
			WritingRecordResponseWriter(base::Span const &span)
				: _adu_writer(span)
			{
			}
		};

	} // namespace modbus
} // namespace base
