#include "MemoryStream.h"

base::MemoryStream::MemoryStream(int32_t max_size)
	: _buffer_context(max_size)
{
}

base::MemoryStream::MemoryStream(base::Span const &span)
	: _buffer_context(span)
{
}

base::Span base::MemoryStream::Span() const
{
	return _buffer_context.Span();
}

/* #region 流属性 */

bool base::MemoryStream::CanRead() const
{
	return true;
}

bool base::MemoryStream::CanWrite() const
{
	return true;
}

bool base::MemoryStream::CanSeek() const
{
	return true;
}

int64_t base::MemoryStream::Length() const
{
	return _length;
}

void base::MemoryStream::SetLength(int64_t value)
{
	if (value > Span().Size())
	{
		throw std::invalid_argument{"value 不能大于缓冲区大小。"};
	}

	_length = value;
	if (_position > _length)
	{
		_position = _length;
	}
}

int64_t base::MemoryStream::Position() const
{
	return _position;
}

void base::MemoryStream::SetPosition(int64_t value)
{
	if (value > _length)
	{
		throw std::invalid_argument{"value 不能大于流的长度。"};
	}

	_position = value;
}

/* #endregion */

/* #region 读写冲关 */

int32_t base::MemoryStream::Read(base::Span const &span)
{
	if (span.Size() == 0)
	{
		throw std::invalid_argument{"不能读取 0 个字节，因为流读取 0 个字节表示流结束了。"};
	}

	if (Position() == Length())
	{
		return 0;
	}

	int32_t have_read = std::min<int32_t>(Length() - Position(), span.Size());

	std::copy(Span().Buffer() + _position,
			  Span().Buffer() + _position + have_read,
			  span.Buffer());

	_position += have_read;
	return have_read;
}

void base::MemoryStream::Write(base::ReadOnlySpan const &span)
{
	if (span.Buffer() == nullptr)
	{
		throw std::invalid_argument{"buffer 不能是空指针。"};
	}

	if (span.Size() > Span().Size() - Position())
	{
		throw std::overflow_error{"缓冲区剩余空间无法接受这么多数据"};
	}

	std::copy(span.Buffer(),
			  span.Buffer() + span.Size(),
			  Span().Buffer() + _position);

	_position += span.Size();
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

/* #endregion */

void base::MemoryStream::Clear()
{
	_position = 0;
	_length = 0;
}
