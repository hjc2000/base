#include "BlockingCircleBufferMemoryStream.h"
#include <base/string/define.h>

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
	base::LockGuard{*_lock};
	return _mstream.Length();
}

void base::BlockingCircleBufferMemoryStream::SetLength(int64_t value)
{
	base::LockGuard{*_lock};
	_mstream.SetLength(value);
}

int32_t base::BlockingCircleBufferMemoryStream::Read(uint8_t *buffer, int32_t offset, int32_t count)
{
	while (true)
	{
		if (_stream_closed)
		{
			throw std::runtime_error{CODE_POS_STR + "流已关闭，无法读取"};
		}

		// 在持有互斥锁的条件下检查，避免误触，以及操作
		{
			base::LockGuard{*_lock};
			if (_mstream.Length() > 0)
			{
				int64_t have_read = _mstream.Read(buffer, offset, count);
				_buffer_consumed_signal->Release();
				return have_read;
			}
		}

		_buffer_avaliable_signal->Acquire();
	}
}

void base::BlockingCircleBufferMemoryStream::Write(uint8_t const *buffer, int32_t offset, int32_t count)
{
	while (true)
	{
		if (_stream_closed)
		{
			throw std::runtime_error{CODE_POS_STR + "流已关闭，无法写入。"};
		}

		{
			base::LockGuard{*_lock};
			if (_mstream.AvailableToWrite() > 0)
			{
				int64_t should_write = std::min(_mstream.AvailableToWrite(), count);
				_mstream.Write(buffer, offset, should_write);
				offset += should_write;
				count -= should_write;
				_buffer_avaliable_signal->Release();
				if (count <= 0)
				{
					return;
				}
			}
		}

		_buffer_consumed_signal->Acquire();
	}
}

void base::BlockingCircleBufferMemoryStream::Flush()
{
	base::LockGuard{*_lock};
	_mstream.Flush();
}

void base::BlockingCircleBufferMemoryStream::Close()
{
	base::LockGuard{*_lock};
	_stream_closed = true;
	_buffer_avaliable_signal->Dispose();
	_buffer_consumed_signal->Dispose();
}

int64_t base::BlockingCircleBufferMemoryStream::Position()
{
	base::LockGuard{*_lock};
	return _mstream.Position();
}

void base::BlockingCircleBufferMemoryStream::SetPosition(int64_t value)
{
	base::LockGuard{*_lock};
	_mstream.SetPosition(value);
}
