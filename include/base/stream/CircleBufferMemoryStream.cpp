#include "CircleBufferMemoryStream.h"

base::CircleBufferMemoryStream::CircleBufferMemoryStream(int32_t size)
{
	_buffer_size = size;
	_start = 0;
	_end = 0;
	_is_full = false;
	_buffer = std::unique_ptr<uint8_t[]>{new uint8_t[size]};
}

/// @brief 递增头指针
/// @param value
void base::CircleBufferMemoryStream::AddHead(int32_t value)
{
	_start = (_start + value) % _buffer_size;
}

/// @brief 递增尾指针
/// @param value
void base::CircleBufferMemoryStream::AddTail(int32_t value)
{
	_end = (_end + value) % _buffer_size;
}

/// @brief 以非环绕方式读取。
///	@warning 从 _start 处开始读取 span，不管会不会超出边界，所以调用本方法前需要检查。
/// @param span
/// @return
void base::CircleBufferMemoryStream::ReadNonCircular(base::Span const &span)
{
	std::copy(_buffer.get() + _start,
			  _buffer.get() + _start + span.Size(),
			  span.Buffer());

	AddHead(span.Size());
	_is_full = false;
}

/// @brief 以非环绕方式写入。
/// @warning 从 _end 处开始往后写入 span，不会管会不会超出边界，所以调用本方法前需要检查。
/// @param span
void base::CircleBufferMemoryStream::WriteNonCircular(base::ReadOnlySpan const &span)
{
	std::copy(span.Buffer(),
			  span.Buffer() + span.Size(),
			  _buffer.get() + _end);

	AddTail(span.Size());
	_is_full = _start == _end;
}

int32_t base::CircleBufferMemoryStream::AvailableToWrite() const
{
	return _buffer_size - Length();
	if (_is_full)
	{
		// 如果缓冲区已满，可用空间为0
		return 0;
	}
	else if (_end >= _start)
	{
		// 如果尾指针在头指针后面，可用空间是缓冲区尾部到尾指针，加上头指针到缓冲区头部的空间
		return _buffer_size - (_end - _start);
	}
	else
	{
		// 如果尾指针在头指针前面，可用空间是头指针到尾指针之间的空间
		return _start - _end;
	}
}

void base::CircleBufferMemoryStream::Clear()
{
	_start = 0;
	_end = 0;
	_is_full = false;
}

bool base::CircleBufferMemoryStream::CanRead() const
{
	return true;
}

bool base::CircleBufferMemoryStream::CanWrite() const
{
	return true;
}

bool base::CircleBufferMemoryStream::CanSeek() const
{
	// 循环队列通常不支持随机访问
	return false;
}

int64_t base::CircleBufferMemoryStream::Length() const
{
	if (_is_full)
	{
		return _buffer_size;
	}

	if (_end >= _start)
	{
		return _end - _start;
	}

	/* _start 大于 _end。说明 _end 穿梭了。
	 *
	 * 此时 _start 和 _end 之间是空白区。
	 * 举个例子，假如 _start = n, _end = n - 1，
	 * 则空白的区域大小为：
	 * 		_start - _end = n - (n - 1) = n - n + 1 = 1
	 * 则缓冲区内容长度为：
	 * 		_buffer_size - (_start - _end) = _buffer_size - 1。
	 *
	 * 上面我们用特殊性的例子得出了具有普遍性的公式：
	 * 		 _buffer_size - (_start - _end)。
	 */
	return _buffer_size - (_start - _end);
}

void base::CircleBufferMemoryStream::SetLength(int64_t value)
{
	throw std::runtime_error{"不支持的操作"};
}

int32_t base::CircleBufferMemoryStream::Read(base::Span const &span)
{
	if (span.Buffer() == nullptr)
	{
		throw std::invalid_argument{"span 的缓冲区不能是空指针"};
	}

	if (span.Size() == 0)
	{
		throw std::invalid_argument{"span 的大小不能是 0 个字节。"};
	}

	if (Empty())
	{
		// 缓冲区为空
		return 0;
	}

	/**
	 * span 如果太大，本流的数据无法充满他，所以需要将 span 切片，最大只能到 Length.
	 * 如果 span 的大小本来就小于 Length 了，则保持原大小。
	 */
	base::Span const should_read_span = span.Slice(base::Range{0, std::min<int32_t>(span.Size(), Length())});
	if (_end > _start)
	{
		// 尾指针在头指针的后面，当前缓冲区内的数据没有环绕，所以读取时也不需要环绕
		ReadNonCircular(should_read_span);
		return should_read_span.Size();
	}

	// 执行到这里说明 _end <= _head，此时缓冲区内的数据发生了环绕，所以读取时有可能要环绕。
	if (should_read_span.Size() <= _buffer_size - _start)
	{
		// 此时从 _start 到缓冲区末尾的数据刚好够本次读取，不用环绕
		ReadNonCircular(should_read_span);
		return should_read_span.Size();
	}

	// 执行到这里说明要环绕了。
	// 先读取从 _start 开始到缓冲区末尾的数据。因为这部分可以先用非环绕的方式读出来。
	base::Span span1 = should_read_span.Slice(base::Range{0, _buffer_size - _start});
	ReadNonCircular(span1);

	// 此时变成非环绕模式了，因为刚才的读取让 _start 发生环绕，已经变成 0 了。
	base::Span span2 = should_read_span.Slice(base::Range{span1.Size(), should_read_span.Size()});
	ReadNonCircular(span2);
	return should_read_span.Size();
}

void base::CircleBufferMemoryStream::Write(base::ReadOnlySpan const &span)
{
	if (AvailableToWrite() < span.Size())
	{
		throw std::overflow_error{"缓冲区剩余空间无法接受这么多数据"};
	}

	if (span.Size() <= _buffer_size - _end)
	{
		// _end 到缓冲区尾部的空间刚好够写入，此时不需要环绕
		WriteNonCircular(span);
		return;
	}

	// 需要环绕
	base::ReadOnlySpan span1 = span.Slice(base::Range{0, _buffer_size - _end});
	WriteNonCircular(span1);

	// 此时 _end 已经变成 0 了，继续用 WriteNonCircular 写入剩余的字节
	base::ReadOnlySpan span2 = span.Slice(base::Range{span1.Size(), span.Size()});
	WriteNonCircular(span2);
}

int64_t base::CircleBufferMemoryStream::Position() const
{
	throw std::runtime_error{"不支持的操作"};
}

void base::CircleBufferMemoryStream::SetPosition(int64_t value)
{
	throw std::runtime_error{"不支持的操作"};
}
