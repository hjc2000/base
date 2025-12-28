#include "Stream.h" // IWYU pragma: keep
#include <cstdint>
#include <memory>

void base::Stream::CopyTo(std::shared_ptr<base::Stream> dst_stream,
						  std::shared_ptr<base::CancellationToken> cancellation_token)
{
#if HAS_THREAD

	uint8_t stack_temp_buffer[1024];

	uint8_t *temp_buffer = stack_temp_buffer;
	int64_t temp_buffer_size = 1024;

	std::unique_ptr<uint8_t[]> heap_temp_buffer;

	if (Length() > 1 * 1024 * 1024)
	{
		temp_buffer_size = std::min<int64_t>(Length(), 16 * 1024 * 1024);
		heap_temp_buffer = std::unique_ptr<uint8_t[]>{new uint8_t[temp_buffer_size]};
		temp_buffer = heap_temp_buffer.get();
	}

#else

	uint8_t temp_buffer[32];
	int64_t temp_buffer_size = 32;

#endif

	while (true)
	{
		base::throw_if_cancellation_is_requested(cancellation_token);

		int64_t have_read = Read(temp_buffer, 0, temp_buffer_size);

		if (have_read == 0)
		{
			return;
		}

		dst_stream->Write(temp_buffer, 0, have_read);
	}
}
