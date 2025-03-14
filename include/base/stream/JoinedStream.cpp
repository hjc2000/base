#include "JoinedStream.h"

std::shared_ptr<base::Stream> base::JoinedStream::TryGetStream()
{
	if (_stream_queue.Count() == 0)
	{
		_current_stream_end_event();
	}

	try
	{
		return _stream_queue.Dequeue();
	}
	catch (...)
	{
		return nullptr;
	}
}

void base::JoinedStream::AppendStream(std::shared_ptr<base::Stream> stream)
{
	_stream_queue.Enqueue(stream);
}

bool base::JoinedStream::CanRead() const
{
	return true;
}

bool base::JoinedStream::CanWrite() const
{
	return false;
}

bool base::JoinedStream::CanSeek() const
{
	return false;
}

int64_t base::JoinedStream::Length() const
{
	throw std::runtime_error{"不支持的操作"};
}

void base::JoinedStream::SetLength(int64_t value)
{
	throw std::runtime_error{"不支持的操作"};
}

int32_t base::JoinedStream::Read(base::Span const &span)
{
	while (true)
	{
		if (_current_stream == nullptr)
		{
			_current_stream = TryGetStream();
			if (_current_stream == nullptr)
			{
				// 尝试获取流之后 _current_stream 仍然是空，JoinedStream 结束。
				return 0;
			}
		}

		// 执行到这里说明 _current_stream 不为空
		int32_t have_read = _current_stream->Read(span);
		if (have_read == 0)
		{
			// 此流结束了，应该尝试获取下一个流继续读取
			_current_stream = nullptr;
			continue;
		}

		_position += have_read;
		return have_read;
	}
}

void base::JoinedStream::Write(base::ReadOnlySpan const &span)
{
	throw std::runtime_error{"不支持的操作"};
}

void base::JoinedStream::Flush()
{
	throw std::runtime_error{"不支持的操作"};
}

void base::JoinedStream::Close()
{
}

int64_t base::JoinedStream::Position() const
{
	return _position;
}

void base::JoinedStream::SetPosition(int64_t value)
{
	throw std::runtime_error{"不支持的操作"};
}
