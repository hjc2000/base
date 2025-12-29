#include "Stream.h" // IWYU pragma: keep
#include "base/string/define.h"
#include <cstdint>
#include <memory>
#include <stdexcept>

void base::Stream::CopyTo(std::shared_ptr<base::Stream> dst_stream,
						  std::shared_ptr<base::CancellationToken> cancellation_token)
{
#if HAS_THREAD

	uint8_t temp_buffer[1024];

#else

	uint8_t temp_buffer[32];

#endif

	while (true)
	{
		base::throw_if_cancellation_is_requested(cancellation_token);

		int64_t have_read = Read(temp_buffer, 0, sizeof(temp_buffer));

		if (have_read == 0)
		{
			return;
		}

		dst_stream->Write(temp_buffer, 0, have_read);
	}
}

void base::Stream::CopyTo(std::shared_ptr<base::Stream> dst_stream,
						  int64_t temp_buffer_size,
						  std::shared_ptr<base::CancellationToken> cancellation_token)
{
	if (temp_buffer_size <= 0)
	{
		throw std::invalid_argument{CODE_POS_STR + "temp_buffer_size 不能 <= 0."};
	}

	std::unique_ptr<uint8_t[]> temp_buffer{new uint8_t[temp_buffer_size]};

	while (true)
	{
		base::throw_if_cancellation_is_requested(cancellation_token);

		int64_t have_read = Read(temp_buffer.get(), 0, temp_buffer_size);

		if (have_read == 0)
		{
			return;
		}

		dst_stream->Write(temp_buffer.get(), 0, have_read);
	}
}
