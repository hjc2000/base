#include "Stream.h"

int32_t base::Stream::ReadExactly(base::Span const &span)
{
	base::Span remain_span{span};
	while (remain_span.Size() > 0)
	{
		int32_t have_read = Read(remain_span);
		if (have_read == 0)
		{
			// 到达流结尾了，读到多少就多少，直接返回
			break;
		}

		remain_span = remain_span.Slice(base::Range{have_read, remain_span.Size()});
	}

	return span.Size() - remain_span.Size();
}

void base::Stream::CopyTo(std::shared_ptr<base::Stream> dst_stream,
						  std::shared_ptr<base::CancellationToken> cancellationToken)
{
#if HAS_THREAD
	uint8_t temp_buffer[1024];
#else
	uint8_t temp_buffer[32];
#endif

	while (true)
	{
		if (cancellationToken->IsCancellationRequested())
		{
			throw base::TaskCanceledException{};
		}

		int32_t have_read = Read(temp_buffer, 0, sizeof(temp_buffer));
		if (have_read == 0)
		{
			return;
		}

		dst_stream->Write(temp_buffer, 0, have_read);
	}
}
