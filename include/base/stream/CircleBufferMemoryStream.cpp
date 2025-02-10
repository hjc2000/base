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
///	@warning 从 _start 处开始读取 count 个字节，不管会不会超出边界。
///			 所以调用本方法前需要检查。
///
/// @param buffer
/// @param offset
/// @param count
/// @return
int32_t base::CircleBufferMemoryStream::ReadNonCircular(uint8_t *buffer, int32_t offset, int32_t count)
{
	std::copy(_buffer.get() + _start,
			  _buffer.get() + _start + count,
			  buffer + offset);

	AddHead(count);
	_is_full = false;
	return count;
}

/// @brief 以非环绕方式写入。
/// @warning 从 _end 的位置开始往后写入 count 个字节，不会管会不会超出边界，
///			 所以调用本方法前需要检查。
///
/// @param buffer
/// @param offset
/// @param count
void base::CircleBufferMemoryStream::WriteNonCircular(uint8_t const *buffer, int32_t offset, int32_t count)
{
	std::copy(buffer + offset,
			  buffer + offset + count,
			  _buffer.get() + _end);

	AddTail(count);
	_is_full = _start == _end;
}

int32_t base::CircleBufferMemoryStream::AvailableToWrite() const
{
	if (_is_full)
	{
		return 0; // 如果缓冲区已满，可用空间为0
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

bool base::CircleBufferMemoryStream::CanRead()
{
	return true;
}

bool base::CircleBufferMemoryStream::CanWrite()
{
	return true;
}

bool base::CircleBufferMemoryStream::CanSeek()
{
	// 循环队列通常不支持随机访问
	return false;
}

int64_t base::CircleBufferMemoryStream::Length()
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
	if (Empty())
	{
		return 0; // 缓冲区为空
	}

	// 应该读取多少字节
	int32_t should_read = std::min<int32_t>(span.Size(), Length());

	if (_end > _start)
	{
		// 尾指针在头指针的后面，当前缓冲区内的数据没有环绕，所以读取时也不需要环绕
		return ReadNonCircular(span.Buffer(), 0, should_read);
	}

	/* 执行到这里说明 _end <= _head，此时缓冲区内的数据发生了环绕，所以读取时有可能要环绕。*/
	if (should_read <= _buffer_size - _start)
	{
		// 此时从 _start 到缓冲区末尾的数据刚好够本次读取，不用环绕
		return ReadNonCircular(span.Buffer(), 0, should_read);
	}

	// 执行到这里说明要环绕了。
	// 先读取从 _start 开始到缓冲区末尾的数据
	int64_t have_read = ReadNonCircular(span.Buffer(), 0, _buffer_size - _start);
	should_read -= have_read;

	// 此时变成非环绕模式了，因为 _start 已经变成 0 了。
	have_read += ReadNonCircular(span.Buffer(), have_read, should_read);
	return have_read;
}

void base::CircleBufferMemoryStream::Write(uint8_t const *buffer, int32_t offset, int32_t count)
{
	if (AvailableToWrite() < count)
	{
		throw std::overflow_error{"缓冲区剩余空间无法接受这么多数据"};
	}

	if (count <= _buffer_size - _end)
	{
		// _end 到缓冲区尾部的空间刚好够写入，此时不需要环绕
		WriteNonCircular(buffer, offset, count);
		return;
	}

	// 需要环绕
	int64_t first_chunk_size = _buffer_size - _end;
	WriteNonCircular(buffer, offset, first_chunk_size);

	// 此时 _end 已经变成 0 了，继续用 WriteNonCircular 写入剩余的字节
	WriteNonCircular(buffer, offset + first_chunk_size, count - first_chunk_size);
}

int64_t base::CircleBufferMemoryStream::Position()
{
	throw std::runtime_error{"不支持的操作"};
}

void base::CircleBufferMemoryStream::SetPosition(int64_t value)
{
	throw std::runtime_error{"不支持的操作"};
}
