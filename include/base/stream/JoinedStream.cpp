#include "JoinedStream.h" // IWYU pragma: keep

int64_t base::JoinedStream::Read(base::Span const &span)
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
		int64_t have_read = _current_stream->Read(span);
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
