#pragma once
#include "base/bit/bit.h"
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

				int high_one_count = base::bit::HighOneCount(byte);
				switch (high_one_count)
				{
				case 0:
					{
						buffer[total_read] = byte;
						total_read++;
						continue;
					}
				case 1:
					{
						// 读取第 1 个字节旧遇到 0b10 开头的字符，是非法的。
						buffer[total_read] = 0xfffd;
						total_read++;
						continue;
					}
				case 2:
					{
						// 0b110 开头，除了当前字节，后续还有 1 个字节的数据。
						continue;
					}
				case 3:
					{
						// 0b1110 开头，除了当前字节，后续还有 2 个字节的数据。
						continue;
					}
				case 4:
					{
						// 0b11110 开头，除了当前字节，后续还有 3 个字节的数据。
						continue;
					}
				default:
					{
						buffer[total_read] = 0xfffd;
						total_read++;
						continue;
					}
				}
			}

			return total_read;
		}
	};

} // namespace base::string::encoding
