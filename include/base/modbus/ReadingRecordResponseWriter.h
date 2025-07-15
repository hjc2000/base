#pragma once
#include "base/modbus/AduWriter.h"

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

		public:
			ReadingRecordResponseWriter(base::Span const &span)
				: _adu_writer(span)
			{
			}
		};

	} // namespace modbus
} // namespace base
