#pragma once
#include "base/stream/Span.h"
#include "base/stream/Stream.h"
#include <cstdint>

namespace base::string::encoding
{
	class Utf8Reader
	{
	private:
		base::Stream &_stream;

	public:
		Utf8Reader(base::Stream &stream)
			: _stream(stream)
		{
		}

		int64_t Read(char32_t *buffer, int64_t count)
		{
			int64_t total_read = 0;

			while (true)
			{
				uint8_t byte;
				int64_t have_read = _stream.Read(base::Span{&byte, 1});
				if (have_read <= 0)
				{
					break;
				}

				if (byte < 0x80)
				{
					buffer[total_read] = byte;
					total_read++;
					continue;
				}
			}

			return total_read;
		}
	};

} // namespace base::string::encoding
