#include "BlockingCircleBufferMemoryStream.h"
#include "base/container/Range.h"

bool base::BlockingCircleBufferMemoryStream::CanRead() const
{
	return true;
}

bool base::BlockingCircleBufferMemoryStream::CanWrite() const
{
	return true;
}

bool base::BlockingCircleBufferMemoryStream::CanSeek() const
{
	return false;
}

int64_t base::BlockingCircleBufferMemoryStream::Length() const
{
	base::LockGuard l{*_lock};
	return _mstream.Length();
}

void base::BlockingCircleBufferMemoryStream::SetLength(int64_t value)
{
	base::LockGuard l{*_lock};
	_mstream.SetLength(value);
}

int64_t base::BlockingCircleBufferMemoryStream::Position() const
{
	base::LockGuard l{*_lock};
	return _mstream.Position();
}

void base::BlockingCircleBufferMemoryStream::SetPosition(int64_t value)
{
	base::LockGuard l{*_lock};
	_mstream.SetPosition(value);
}

int32_t base::BlockingCircleBufferMemoryStream::Read(base::Span const &span)
{
	while (true)
	{
		if (_stream_closed)
		{
			throw std::runtime_error{CODE_POS_STR + "流已关闭，无法读取"};
		}

		// 在持有互斥锁的条件下检查，避免误触，以及操作
		{
			base::LockGuard l{*_lock};
			if (_mstream.Length() > 0)
			{
				int64_t have_read = _mstream.Read(span);
				_buffer_consumed_signal.ReleaseAll();
				return have_read;
			}
		}

		_buffer_avaliable_signal.Acquire();
	}
}

void base::BlockingCircleBufferMemoryStream::Write(base::ReadOnlySpan const &span)
{
	if (span.Size() <= 0)
	{
		return;
	}

	base::ReadOnlySpan remain_span = span;
	while (true)
	{
		if (_stream_closed)
		{
			throw std::runtime_error{CODE_POS_STR + "流已关闭，无法写入。"};
		}

		{
			base::LockGuard l{*_lock};
			if (_mstream.AvailableToWrite() > 0)
			{
				int32_t should_write = std::min(_mstream.AvailableToWrite(), remain_span.Size());
				_mstream.Write(remain_span[base::Range{0, should_write}]);
				remain_span = remain_span[base::Range{should_write, remain_span.Size()}];
				_buffer_avaliable_signal.ReleaseAll();
				if (remain_span.Size() <= 0)
				{
					// 将所有数据写完了，返回
					return;
				}
			}
		}

		// 如果刚才将所有数据写完了，已经返回了，到这里说明没写完，但是流已经满了，需要等待。
		_buffer_consumed_signal.Acquire();
	}
}

void base::BlockingCircleBufferMemoryStream::Flush()
{
	base::LockGuard l{*_lock};
	_mstream.Flush();
}

void base::BlockingCircleBufferMemoryStream::Close()
{
	base::LockGuard l{*_lock};
	_stream_closed = true;
	_buffer_avaliable_signal.Dispose();
	_buffer_consumed_signal.Dispose();
}
