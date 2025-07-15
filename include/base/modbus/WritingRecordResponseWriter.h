#pragma once
#include "base/modbus/AduWriter.h"

namespace base
{
	namespace modbus
	{
		class WritingRecordResponseWriter
		{
		private:
			base::modbus::AduWriter _adu_writer;

		public:
			WritingRecordResponseWriter(base::Span const &span)
				: _adu_writer(span)
			{
			}
		};

	} // namespace modbus
} // namespace base
