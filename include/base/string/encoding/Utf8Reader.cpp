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
	// 检查该直接最高位起的连续 1 的个数。
	int high_one_count = base::bit::HighOneCount(byte);

	switch (high_one_count)
	{
	case 0:
		{
			// 0 个高位 1 说明是 ascii 兼容字符。
			return true;
		}
	case 1:
		{
			// 1 个高位 1 说明是 UTF8 的一个序列中的接续字符，不是起始字符。
			return false;
		}
	case 2:
	case 3:
	case 4:
		{
			// 2-4 个高位 1 说明是 UTF8 的一个序列中的起始字符。
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

void base::string::encoding::Utf8Reader::DecodeOneByteCaracter(uint8_t byte1)
{
	char32_t decode_result = byte1;

	if (!IsValidOneByteUnicodeCharacter(decode_result))
	{
		_reading_context._span[_reading_context._total_read] = ReplacementCharacter();
		_reading_context._total_read++;
		return;
	}

	// 最高位开始数，有 0 个 1, 即以 0 开头。这种 utf8 字符与 ascii 兼容。
	_reading_context._span[_reading_context._total_read] = decode_result;
	_reading_context._total_read++;
}

void base::string::encoding::Utf8Reader::DecodeTwoByteCaracter(uint8_t byte1)
{
	// 0b110 开头，除了当前字节，后续还有 1 个字节的数据。
	FillHalfQueue();
	if (_queue.Count() < 1)
	{
		// 后续还需要 1 个字节，但是已经没有了。
		_reading_context._span[_reading_context._total_read] = ReplacementCharacter();
		_reading_context._total_read++;
		return;
	}

	uint8_t byte2 = _queue.PopFront();

	if (!IsValidUtf8ContinueByte(byte2))
	{
		// 有可能是首字节，所以放回队列，让下个循环的 SeekToNextSequence
		// 去定位到合法的首字节。
		_queue.PushFront(byte2);
		_reading_context._span[_reading_context._total_read] = ReplacementCharacter();
		_reading_context._total_read++;
		return;
	}

	byte1 = base::bit::ReadBits(byte1, 0, 5);
	byte2 = base::bit::ReadBits(byte2, 0, 6);

	char32_t decode_result = 0;
	decode_result |= byte1 << (6 * 1);
	decode_result |= byte2 << (6 * 0);

	if (!IsValidTwoByteUnicodeCharacter(decode_result))
	{
		_reading_context._span[_reading_context._total_read] = ReplacementCharacter();
		_reading_context._total_read++;
		return;
	}

	_reading_context._span[_reading_context._total_read] = decode_result;
	_reading_context._total_read++;
}

void base::string::encoding::Utf8Reader::DecodeThreeByteCaracter(uint8_t byte1)
{
	// 0b1110 开头，除了当前字节，后续还有 2 个字节的数据。
	FillHalfQueue();
	if (_queue.Count() < 2)
	{
		_reading_context._span[_reading_context._total_read] = ReplacementCharacter();
		_reading_context._total_read++;
		return;
	}

	uint8_t byte2 = _queue.PopFront();
	uint8_t byte3 = _queue.PopFront();

	if (!IsValidUtf8ContinueByte(byte2))
	{
		// 有可能是首字节，所以放回队列，让下个循环的 SeekToNextSequence
		// 去定位到合法的首字节。
		_queue.PushFront(byte2);
		_reading_context._span[_reading_context._total_read] = ReplacementCharacter();
		_reading_context._total_read++;
		return;
	}

	if (!IsValidUtf8ContinueByte(byte3))
	{
		// 有可能是首字节，所以放回队列，让下个循环的 SeekToNextSequence
		// 去定位到合法的首字节。
		_queue.PushFront(byte3);
		_reading_context._span[_reading_context._total_read] = ReplacementCharacter();
		_reading_context._total_read++;
		return;
	}

	byte1 = base::bit::ReadBits(byte1, 0, 4);
	byte2 = base::bit::ReadBits(byte2, 0, 6);
	byte3 = base::bit::ReadBits(byte3, 0, 6);

	char32_t decode_result = 0;
	decode_result |= byte1 << (6 * 2);
	decode_result |= byte2 << (6 * 1);
	decode_result |= byte3 << (6 * 0);

	if (!IsValidThreeByteUnicodeCharacter(decode_result))
	{
		_reading_context._span[_reading_context._total_read] = ReplacementCharacter();
		_reading_context._total_read++;
		return;
	}

	_reading_context._span[_reading_context._total_read] = decode_result;
	_reading_context._total_read++;
}

void base::string::encoding::Utf8Reader::DecodeFourByteCaracter(uint8_t byte1)
{
	// 0b1111'0 开头，除了当前字节，后续还有 3 个字节的数据。
	FillHalfQueue();
	if (_queue.Count() < 3)
	{
		_reading_context._span[_reading_context._total_read] = ReplacementCharacter();
		_reading_context._total_read++;
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
		_reading_context._span[_reading_context._total_read] = ReplacementCharacter();
		_reading_context._total_read++;
		return;
	}

	if (!IsValidUtf8ContinueByte(byte3))
	{
		// 有可能是首字节，所以放回队列，让下个循环的 SeekToNextSequence
		// 去定位到合法的首字节。
		_queue.PushFront(byte3);
		_reading_context._span[_reading_context._total_read] = ReplacementCharacter();
		_reading_context._total_read++;
		return;
	}

	if (!IsValidUtf8ContinueByte(byte4))
	{
		// 有可能是首字节，所以放回队列，让下个循环的 SeekToNextSequence
		// 去定位到合法的首字节。
		_queue.PushFront(byte4);
		_reading_context._span[_reading_context._total_read] = ReplacementCharacter();
		_reading_context._total_read++;
		return;
	}

	byte1 = base::bit::ReadBits(byte1, 0, 3);
	byte2 = base::bit::ReadBits(byte2, 0, 6);
	byte3 = base::bit::ReadBits(byte3, 0, 6);
	byte4 = base::bit::ReadBits(byte4, 0, 6);

	char32_t decode_result = 0;
	decode_result |= byte1 << (6 * 3);
	decode_result |= byte2 << (6 * 2);
	decode_result |= byte3 << (6 * 1);
	decode_result |= byte4 << (6 * 0);

	if (!IsValidFourByteUnicodeCharacter(decode_result))
	{
		_reading_context._span[_reading_context._total_read] = ReplacementCharacter();
		_reading_context._total_read++;
		return;
	}

	_reading_context._span[_reading_context._total_read] = decode_result;
	_reading_context._total_read++;
}

void base::string::encoding::Utf8Reader::DecodeOneCharacter()
{
	uint8_t byte1 = _queue.PopFront();

	if (!IsValidUtf8SequenceStart(byte1))
	{
		_reading_context._span[_reading_context._total_read] = ReplacementCharacter();
		_reading_context._total_read++;
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
			DecodeOneByteCaracter(byte1);
			return;
		}
	case 2:
		{
			DecodeTwoByteCaracter(byte1);
			return;
		}
	case 3:
		{
			DecodeThreeByteCaracter(byte1);
			return;
		}
	case 4:
		{
			DecodeFourByteCaracter(byte1);
			return;
		}
	default:
		{
			throw std::runtime_error{CODE_POS_STR + "经过 SeekToNextSequence 处理后，不应该走入此分支。"};
		}
	}
}

int64_t base::string::encoding::Utf8Reader::Read(base::ArraySpan<char32_t> const &span)
{
	_reading_context._span = span;
	_reading_context._total_read = 0;

	while (true)
	{
		if (_reading_context._total_read >= _reading_context._span.Count())
		{
			return _reading_context._total_read;
		}

		FillHalfQueue();
		if (_queue.Count() <= 0)
		{
			return _reading_context._total_read;
		}

		DecodeOneCharacter();
	}
}
