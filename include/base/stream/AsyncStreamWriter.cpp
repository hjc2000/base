#include "AsyncStreamWriter.h" // IWYU pragma: keep

void base::AsyncStreamWriter::ThreadFunc()
{
	while (true)
	{
		// 不需要检查 _disposed 为 true 后返回。只管读取 _buffer_stream 就行了，
		// 在释放阶段，_buffer_stream 会被关闭，在读出残留数据后 Read 方法会返回 0,
		// 此时就可以退出线程了。
		//
		// 如果检查 _buffer_stream 为 true 直接退出，会导致残留数据没被读取。
		int64_t have_read = _buffer_stream->Read(base::Span{_copy_temp_buffer, sizeof(_copy_temp_buffer)});
		if (have_read == 0)
		{
			return;
		}

		_stream->Write(base::ReadOnlySpan{_copy_temp_buffer, have_read});
	}
}
