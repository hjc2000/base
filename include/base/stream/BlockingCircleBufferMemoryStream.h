#pragma once
#ifndef HAS_THREAD
#define HAS_THREAD 0
#endif

#if HAS_THREAD

#include <base/stream/CircleBufferMemoryStream.h>
#include <condition_variable>
#include <mutex>

namespace base
{
	/// @brief 带阻塞功能的环形缓冲区的内存流。
	class BlockingCircleBufferMemoryStream
		: public base::Stream
	{
	private:
		base::CircleBufferMemoryStream _mstream;
		std::mutex _lock;
		std::atomic_bool _stream_closed = false;

		/// @brief 流中的数据被消费了，现在处于不是满的状态
		std::condition_variable _buffer_consumed;

		/// @brief 流中有数据可用。
		std::condition_variable _buffer_avaliable;

	public:
		BlockingCircleBufferMemoryStream(int32_t max_size) : _mstream(max_size)
		{
		}

		~BlockingCircleBufferMemoryStream()
		{
			Close();
		}

#pragma region 通过 Stream 继承
		bool CanRead() override;
		bool CanWrite() override;
		bool CanSeek() override;
		int64_t Length() override;
		void SetLength(int64_t value) override;
		int32_t Read(uint8_t *buffer, int32_t offset, int32_t count) override;
		void Write(uint8_t const *buffer, int32_t offset, int32_t count) override;
		void Flush() override;

		/// @brief 结束流。
		/// @note 结束后，写入的数据会被丢弃。Read 方法在读取完缓冲区的数据后，将永远返回 0.
		/// @note 结束后，会取消所有阻塞，且不会再阻塞。
		void Close() override;

		int64_t Position() override;
		void SetPosition(int64_t value) override;
#pragma endregion
	};
}

#endif // HAS_THREAD
