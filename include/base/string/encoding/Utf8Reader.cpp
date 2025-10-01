#include "Utf8Reader.h" // IWYU pragma: keep
#include "base/bit/bit.h"
#include "base/stream/Span.h"
#include "base/string/define.h"
#include <cstdint>
#include <stdexcept>

void base::string::encoding::Utf8Reader::FillHalfQueue()
{
	while (true)
	{
		if (_queue.Count() >= _queue.Capacity() / 2)
		{
			return;
		}

		uint8_t byte;
		int64_t have_read = _stream.Read(base::Span{&byte, 1});
		if (have_read <= 0)
		{
			return;
		}

		_queue.PushBack(byte);
	}
}

bool base::string::encoding::Utf8Reader::IsValidUtf8SequenceStart(uint8_t byte)
{
	int high_one_count = base::bit::HighOneCount(byte);

	switch (high_one_count)
	{
	case 0:
		{
			return true;
		}
	case 1:
		{
			return false;
		}
	case 2:
	case 3:
	case 4:
		{
			return true;
		}
	default:
		{
			return false;
		}
	}
}

void base::string::encoding::Utf8Reader::SeekToNextSequence()
{
	while (true)
	{
		FillHalfQueue();
		if (_queue.Count() <= 0)
		{
			return;
		}

		uint8_t byte = _queue.PopFront();

		if (IsValidUtf8SequenceStart(byte))
		{
			_queue.PushFront(byte);
			return;
		}
	}
}

void base::string::encoding::Utf8Reader::DecodeOneCharacter()
{
	uint8_t byte1 = _queue.PopFront();

	if (!IsValidUtf8SequenceStart(byte1))
	{
		_span[_total_read] = ReplacementCharacter();
		_total_read++;
		SeekToNextSequence();
		return;
	}

	// 经过 SeekToNextSequence 处理后，
	// 到这里可以确定 byte1 是一个 UTF-8 序列的开头。
	int high_one_count = base::bit::HighOneCount(byte1);

	switch (high_one_count)
	{
	case 0:
		{
			char32_t ret = byte1;

			if (!IsValidOneByteUnicodeCharacter(ret))
			{
				_span[_total_read] = ReplacementCharacter();
				_total_read++;
				return;
			}

			// 最高位开始数，有 0 个 1, 即以 0 开头。这种 utf8 字符与 ascii 兼容。
			_span[_total_read] = ret;
			_total_read++;
			return;
		}
	case 2:
		{
			// 0b110 开头，除了当前字节，后续还有 1 个字节的数据。
			FillHalfQueue();
			if (_queue.Count() < 1)
			{
				// 后续还需要 1 个字节，但是已经没有了。
				_span[_total_read] = ReplacementCharacter();
				_total_read++;
				return;
			}

			uint8_t byte2 = _queue.PopFront();

			if (!IsValidUtf8ContinueByte(byte2))
			{
				// 有可能是首字节，所以放回队列，让下个循环的 SeekToNextSequence
				// 去定位到合法的首字节。
				_queue.PushFront(byte2);
				_span[_total_read] = ReplacementCharacter();
				_total_read++;
				return;
			}

			byte1 = base::bit::ReadBits(byte1, 0, 5);
			byte2 = base::bit::ReadBits(byte2, 0, 6);

			char32_t ret = 0;
			ret |= byte1 << (6 * 1);
			ret |= byte2 << (6 * 0);

			if (!IsValidTwoByteUnicodeCharacter(ret))
			{
				_span[_total_read] = ReplacementCharacter();
				_total_read++;
				return;
			}

			_span[_total_read] = ret;
			_total_read++;
			return;
		}
	case 3:
		{
			// 0b1110 开头，除了当前字节，后续还有 2 个字节的数据。
			FillHalfQueue();
			if (_queue.Count() < 2)
			{
				_span[_total_read] = ReplacementCharacter();
				_total_read++;
				return;
			}

			uint8_t byte2 = _queue.PopFront();
			uint8_t byte3 = _queue.PopFront();

			if (!IsValidUtf8ContinueByte(byte2))
			{
				// 有可能是首字节，所以放回队列，让下个循环的 SeekToNextSequence
				// 去定位到合法的首字节。
				_queue.PushFront(byte2);
				_span[_total_read] = ReplacementCharacter();
				_total_read++;
				return;
			}

			if (!IsValidUtf8ContinueByte(byte3))
			{
				// 有可能是首字节，所以放回队列，让下个循环的 SeekToNextSequence
				// 去定位到合法的首字节。
				_queue.PushFront(byte3);
				_span[_total_read] = ReplacementCharacter();
				_total_read++;
				return;
			}

			byte1 = base::bit::ReadBits(byte1, 0, 4);
			byte2 = base::bit::ReadBits(byte2, 0, 6);
			byte3 = base::bit::ReadBits(byte3, 0, 6);

			char32_t ret = 0;
			ret |= byte1 << (6 * 2);
			ret |= byte2 << (6 * 1);
			ret |= byte3 << (6 * 0);

			if (!IsValidThreeByteUnicodeCharacter(ret))
			{
				_span[_total_read] = ReplacementCharacter();
				_total_read++;
				return;
			}

			_span[_total_read] = ret;
			_total_read++;
			return;
		}
	case 4:
		{
			// 0b1111'0 开头，除了当前字节，后续还有 3 个字节的数据。
			FillHalfQueue();
			if (_queue.Count() < 3)
			{
				_span[_total_read] = ReplacementCharacter();
				_total_read++;
				return;
			}

			uint8_t byte2 = _queue.PopFront();
			uint8_t byte3 = _queue.PopFront();
			uint8_t byte4 = _queue.PopFront();

			if (!IsValidUtf8ContinueByte(byte2))
			{
				// 有可能是首字节，所以放回队列，让下个循环的 SeekToNextSequence
				// 去定位到合法的首字节。
				_queue.PushFront(byte2);
				_span[_total_read] = ReplacementCharacter();
				_total_read++;
				return;
			}

			if (!IsValidUtf8ContinueByte(byte3))
			{
				// 有可能是首字节，所以放回队列，让下个循环的 SeekToNextSequence
				// 去定位到合法的首字节。
				_queue.PushFront(byte3);
				_span[_total_read] = ReplacementCharacter();
				_total_read++;
				return;
			}

			if (!IsValidUtf8ContinueByte(byte4))
			{
				// 有可能是首字节，所以放回队列，让下个循环的 SeekToNextSequence
				// 去定位到合法的首字节。
				_queue.PushFront(byte4);
				_span[_total_read] = ReplacementCharacter();
				_total_read++;
				return;
			}

			byte1 = base::bit::ReadBits(byte1, 0, 3);
			byte2 = base::bit::ReadBits(byte2, 0, 6);
			byte3 = base::bit::ReadBits(byte3, 0, 6);
			byte4 = base::bit::ReadBits(byte4, 0, 6);

			char32_t ret = 0;
			ret |= byte1 << (6 * 3);
			ret |= byte2 << (6 * 2);
			ret |= byte3 << (6 * 1);
			ret |= byte4 << (6 * 0);

			if (!IsValidFourByteUnicodeCharacter(ret))
			{
				_span[_total_read] = ReplacementCharacter();
				_total_read++;
				return;
			}

			_span[_total_read] = ret;
			_total_read++;
			return;
		}
	default:
		{
			throw std::runtime_error{CODE_POS_STR + "经过定位到合法的起始字节后，不应该走入此分支。"};
		}
	}
}
