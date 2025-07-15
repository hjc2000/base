#pragma once
#include "base/modbus/AduReader.h"
#include "base/stream/ReadOnlySpan.h"

namespace base
{
	namespace modbus
	{
		class WritingBitsRequestReader
		{
		private:
			base::modbus::AduReader _adu_reader;

		public:
			WritingBitsRequestReader(base::ReadOnlySpan const &span)
				: _adu_reader(span)
			{
			}
		};

	} // namespace modbus
} // namespace base
