#pragma once
#include <base/container/Queue.h>
#include <base/delegate/Delegate.h>
#include <base/pch.h>
#include <base/stream/Stream.h>

namespace base
{
	/// @brief 将多个流串联在一起形成一个流。
	class JoinedStream final :
		public base::Stream
	{
	private:
		/// @brief 用来统计总共从 Read 函数中读取过多少字节。
		int64_t _position = 0;
		Queue<std::shared_ptr<base::Stream>> _stream_queue{};
		std::shared_ptr<base::Stream> _current_stream;
		base::Delegate<> _current_stream_end_event;

		/// @brief 尝试从队列中获取流，如果队列为空，会触发回调然后再尝试退队。如果实在获取不到新的流，
		/// 本方法会返回 nullptr。
		/// @return
		std::shared_ptr<base::Stream> TryGetStream();

	public:
		/// @brief 当前流读到尽头时就会触发此事件。
		/// @note 需要调用 AppendStream 方法添加流到本对象，否则 JoinedStream 将结束。
		/// @return
		base::IEvent<> &CurrentStreamEndEvent()
		{
			return _current_stream_end_event;
		}

		/// @brief 向本对象中追加流。如果不追加，在队列中所有流都读完后，JoinedStream 也将结束。
		/// @param stream
		void AppendStream(std::shared_ptr<base::Stream> stream);

		bool CanRead() const override;
		bool CanWrite() const override;
		bool CanSeek() const override;

		int64_t Length() const override;
		void SetLength(int64_t value) override;

		virtual int32_t Read(base::Span const &span) override;
		virtual void Write(base::ReadOnlySpan const &span) override;

		void Flush() override;
		void Close() override;

		int64_t Position() const override;
		void SetPosition(int64_t value) override;
	};
} // namespace base
