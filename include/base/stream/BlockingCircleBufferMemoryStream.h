#pragma once
#include <base/stream/CircleBufferMemoryStream.h>
#include <base/task/IMutex.h>
#include <base/task/ISemaphore.h>

namespace base
{
	/// @brief 带阻塞功能的环形缓冲区的内存流。
	class BlockingCircleBufferMemoryStream final :
		public base::Stream
	{
	private:
		base::CircleBufferMemoryStream _mstream;
		std::atomic_bool _stream_closed = false;
		std::shared_ptr<base::IMutex> _lock = base::di::CreateMutex();

		/// @brief 流中的数据被消费了，现在处于不是满的状态
		std::shared_ptr<base::ISemaphore> _buffer_consumed_signal = base::di::CreateSemaphore(1);

		/// @brief 流中有数据可用。
		std::shared_ptr<base::ISemaphore> _buffer_avaliable_signal = base::di::CreateSemaphore(0);

	public:
		BlockingCircleBufferMemoryStream(int32_t max_size)
			: _mstream(max_size)
		{
		}

		~BlockingCircleBufferMemoryStream()
		{
			Close();
		}

#pragma region 通过 Stream 继承
		virtual bool CanRead() const override;
		virtual bool CanWrite() const override;
		virtual bool CanSeek() const override;
		virtual int64_t Length() const override;
		virtual void SetLength(int64_t value) override;
		virtual int32_t Read(base::Span const &span) override;
		virtual void Write(base::ReadOnlySpan const &span) override;
		virtual void Flush() override;

		/// @brief 结束流。
		/// @note 结束后，写入的数据会被丢弃。Read 方法在读取完缓冲区的数据后，将永远返回 0.
		/// @note 结束后，会取消所有阻塞，且不会再阻塞。
		virtual void Close() override;

		virtual int64_t Position() const override;
		virtual void SetPosition(int64_t value) override;
#pragma endregion
	};
} // namespace base
