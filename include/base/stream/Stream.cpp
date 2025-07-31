#include "Stream.h" // IWYU pragma: keep

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
		cancellationToken->ThrowIfCancellationIsRequested();
		int64_t have_read = Read(temp_buffer, 0, sizeof(temp_buffer));
		if (have_read == 0)
		{
			return;
		}

		dst_stream->Write(temp_buffer, 0, have_read);
	}
}
