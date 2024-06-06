#ifndef HAS_THREAD
#define HAS_THREAD 0
#endif

#include"Stream.h"

using namespace base;

int32_t Stream::ReadAtLeast(uint8_t *buffer, int32_t offset, int32_t minimum_bytes)
{
	return ReadExactly(buffer, offset, minimum_bytes);
}

int32_t Stream::ReadExactly(uint8_t *buffer, int32_t offset, int32_t count)
{
	int64_t total_read = 0;
	while (true)
	{
		int64_t remain_count = count - total_read;
		if (remain_count <= 0)
		{
			// 读取完成，返回
			return total_read;
		}

		int64_t have_read = Read(buffer, offset + total_read, remain_count);
		if (have_read == 0)
		{
			// 到达流结尾了，读到多少就多少，直接返回
			return total_read;
		}

		total_read += have_read;
	}
}

void Stream::CopyTo(
	std::shared_ptr<base::Stream> dst_stream,
	std::shared_ptr<base::CancellationToken> cancellationToken
)
{
	#if HAS_THREAD
	uint8_t temp_buf[1024 * 16];
	#else
	uint8_t temp_buf[128];
	#endif

	while (true)
	{
		if (cancellationToken && cancellationToken->IsCancellationRequested())
		{
			throw base::TaskCanceledException { };
		}

		int32_t have_read = Read(temp_buf, 0, sizeof(temp_buf));
		if (have_read == 0)
		{
			return;
		}

		dst_stream->Write(temp_buf, 0, have_read);
	}
}
