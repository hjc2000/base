#include "BlockingCircleBufferMemoryStream.h"

#if HAS_THREAD

bool base::BlockingCircleBufferMemoryStream::CanRead()
{
	return true;
}

bool base::BlockingCircleBufferMemoryStream::CanWrite()
{
	return true;
}

bool base::BlockingCircleBufferMemoryStream::CanSeek()
{
	return false;
}

int64_t base::BlockingCircleBufferMemoryStream::Length()
{
	std::unique_lock l(_lock);
	return _mstream.Length();
}

void base::BlockingCircleBufferMemoryStream::SetLength(int64_t value)
{
	std::unique_lock l(_lock);
	_mstream.SetLength(value);
}

int32_t base::BlockingCircleBufferMemoryStream::Read(uint8_t *buffer, int32_t offset, int32_t count)
{
	std::unique_lock l(_lock);

	// 等待流中有数据可用
	auto p_func = [&]() -> bool
	{
		if (_stream_closed)
		{
			return true;
		}

		return _mstream.Length();
	};
	_buffer_avaliable.wait(l, p_func);

	int64_t have_read = _mstream.Read(buffer, offset, count);
	_buffer_consumed.notify_all();
	return have_read;
}

void base::BlockingCircleBufferMemoryStream::Write(uint8_t const *buffer, int32_t offset, int32_t count)
{
	std::unique_lock l(_lock);

	while (count > 0)
	{
		if (_stream_closed)
		{
			return;
		}

		// 等待流缓冲区中有空间可写
		auto p_func = [&]() -> bool
		{
			if (_stream_closed)
			{
				return true;
			}

			return _mstream.AvailableToWrite();
		};
		_buffer_consumed.wait(l, p_func);

		int64_t should_write = std::min(_mstream.AvailableToWrite(), count);
		_mstream.Write(buffer, offset, should_write);
		offset += should_write;
		count -= should_write;
		_buffer_avaliable.notify_all();
	}
}

void base::BlockingCircleBufferMemoryStream::Flush()
{
	std::unique_lock l(_lock);
	_mstream.Flush();
}

void base::BlockingCircleBufferMemoryStream::Close()
{
	std::unique_lock l(_lock);
	_stream_closed = true;
	_buffer_avaliable.notify_all();
	_buffer_consumed.notify_all();
}

int64_t base::BlockingCircleBufferMemoryStream::Position()
{
	std::unique_lock l(_lock);
	return _mstream.Position();
}

void base::BlockingCircleBufferMemoryStream::SetPosition(int64_t value)
{
	std::unique_lock l(_lock);
	_mstream.SetPosition(value);
}

#endif // HAS_THREAD