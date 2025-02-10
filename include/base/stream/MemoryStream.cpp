#include "MemoryStream.h"

base::MemoryStream::MemoryStream(int32_t max_size)
{
	if (max_size <= 0)
	{
		throw std::invalid_argument{"max_size 不能小于等于 0."};
	}

	_buffer = std::unique_ptr<uint8_t[]>{new uint8_t[max_size]};
	_span = base::Span{_buffer.get(), max_size};
}

base::MemoryStream::MemoryStream(base::Span const &span)
{
	_span = span;
}

uint8_t *base::MemoryStream::Buffer()
{
	return _span.Buffer();
}

int32_t base::MemoryStream::BufferSize() const
{
	return _span.Size();
}

int32_t base::MemoryStream::AvaliableToRead() const
{
	return _length - _position;
}

int32_t base::MemoryStream::AvaliableToWrite() const
{
	return _span.Size() - _position;
}

bool base::MemoryStream::CanRead()
{
	return true;
}

bool base::MemoryStream::CanWrite()
{
	return true;
}

bool base::MemoryStream::CanSeek()
{
	return true;
}

int64_t base::MemoryStream::Length()
{
	return _length;
}

void base::MemoryStream::SetLength(int64_t value)
{
	if (value > _span.Size())
	{
		throw std::invalid_argument{"value 不能大于缓冲区大小。"};
	}

	_length = value;
	if (_position > _length)
	{
		_position = _length;
	}
}

int32_t base::MemoryStream::Read(base::Span const &span)
{
	if (span.Size() == 0)
	{
		throw std::invalid_argument{"不能读取 0 个字节，因为流读取 0 个字节表示流结束了。"};
	}

	if (AvaliableToRead() == 0)
	{
		return 0;
	}

	int32_t have_read;
	if (AvaliableToRead() <= span.Size())
	{
		have_read = AvaliableToRead();
	}
	else
	{
		have_read = span.Size();
	}

	std::copy(_span.Buffer() + _position,
			  _span.Buffer() + _position + have_read,
			  span.Buffer());

	_position += have_read;
	return have_read;
}

void base::MemoryStream::Write(uint8_t const *buffer, int32_t offset, int32_t count)
{
	if (buffer == nullptr)
	{
		throw std::invalid_argument{"buffer 不能是空指针。"};
	}

	if (count > AvaliableToWrite())
	{
		throw std::overflow_error{"缓冲区剩余空间无法接受这么多数据"};
	}

	std::copy(buffer + offset,
			  buffer + offset + count,
			  _span.Buffer() + _position);

	_position += count;
	if (_position > _length)
	{
		// 写完后当前位置超过流的长度，则将流的长度设为当前位置，使流的长度增大。
		_length = _position;
	}
}

void base::MemoryStream::Flush()
{
}

void base::MemoryStream::Close()
{
}

void base::MemoryStream::Clear()
{
	_position = 0;
	_length = 0;
}

int64_t base::MemoryStream::Position()
{
	return _position;
}

void base::MemoryStream::SetPosition(int64_t value)
{
	if (_position > _length)
	{
		throw std::invalid_argument{"value 不能流的长度。"};
	}

	_position = value;
}
