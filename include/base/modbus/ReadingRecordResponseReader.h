#pragma once
#include "base/modbus/AduReader.h"

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

		public:
			ReadingRecordResponseReader(base::ReadOnlySpan const &span)
				: _adu_reader(span)
			{
			}
		};

	} // namespace modbus
} // namespace base
