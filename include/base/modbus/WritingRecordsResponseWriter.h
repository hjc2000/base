#pragma once
#include "base/modbus/AduWriter.h"

namespace base
{
	namespace modbus
	{
		class WritingRecordsResponseWriter
		{
		private:
			base::modbus::AduWriter _adu_writer;

		public:
			WritingRecordsResponseWriter(base::Span const &span)
				: _adu_writer(span)
			{
			}
		};

	} // namespace modbus
} // namespace base
