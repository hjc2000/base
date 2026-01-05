#pragma once
#include "base/container/Queue.h"
#include "base/delegate/Delegate.h"
#include "base/exception/NotSupportedException.h"
#include "base/stream/Stream.h"

namespace base
{
	///
	/// @brief 将多个流串联在一起形成一个流。
	///
	class JoinedStream final :
		public base::Stream
	{
	private:
		///
		/// @brief 用来统计总共从 Read 函数中读取过多少字节。
		///
		int64_t _position = 0;

		Queue<std::shared_ptr<base::Stream>> _stream_queue{};
		std::shared_ptr<base::Stream> _current_stream;
		base::Delegate<> _current_stream_end_event;

		///
		/// @brief 尝试从队列中获取流，如果队列为空，会触发回调然后再尝试退队。如果实在获取不到新的流，
		/// 本方法会返回 nullptr。
		///
		/// @return
		///
		std::shared_ptr<base::Stream> TryGetStream()
		{
			if (_stream_queue.Count() == 0)
			{
				_current_stream_end_event();
			}

			try
			{
				return _stream_queue.Dequeue();
			}
			catch (...)
			{
				return nullptr;
			}
		}

	public:
		///
		/// @brief 当前流读到尽头时就会触发此事件。
		///
		/// @note 需要调用 AppendStream 方法添加流到本对象，否则 JoinedStream 将结束。
		///
		/// @return
		///
		base::IEvent<> &CurrentStreamEndEvent()
		{
			return _current_stream_end_event;
		}

		///
		/// @brief 向本对象中追加流。如果不追加，在队列中所有流都读完后，JoinedStream 也将结束。
		///
		/// @param stream
		///
		void AppendStream(std::shared_ptr<base::Stream> stream)
		{
			_stream_queue.Enqueue(stream);
		}

		/* #region 流属性 */

		///
		/// @brief 本流能否读取。
		///
		/// @return
		///
		virtual bool CanRead() const override
		{
			return true;
		}

		///
		/// @brief 本流能否写入。
		///
		/// @return
		///
		virtual bool CanWrite() const override
		{
			return false;
		}

		///
		/// @brief 本流能否定位。
		///
		/// @return
		///
		virtual bool CanSeek() const override
		{
			return false;
		}

		///
		/// @brief 流的长度
		///
		/// @return
		///
		virtual int64_t Length() const override
		{
			throw base::NotSupportedException{};
		}

		///
		/// @brief 设置流的长度。
		///
		/// @param value
		///
		virtual void SetLength(int64_t value) override
		{
			throw base::NotSupportedException{};
		}

		///
		/// @brief 流当前的位置。
		///
		/// @return
		///
		virtual int64_t Position() const override
		{
			return _position;
		}

		///
		/// @brief 设置流当前的位置。
		///
		/// @param value
		///
		virtual void SetPosition(int64_t value) override
		{
			throw base::NotSupportedException{};
		}

		/* #endregion */

		/* #region 读写冲关 */

		///
		/// @brief 将本流的数据读取到 span 中。
		///
		/// @param span
		///
		/// @return
		///
		virtual int64_t Read(base::Span const &span) override;

		///
		/// @brief 将 span 中的数据写入本流。
		///
		/// @param span
		///
		virtual void Write(base::ReadOnlySpan const &span) override
		{
			throw base::NotSupportedException{};
		}

		///
		/// @brief 冲洗流。
		///
		/// @note 对于写入的数据，作用是将其从内部缓冲区转移到底层。
		/// @note 对于内部的可以读取但尚未读取的数据，一般不会有什么作用。Flush 没见过对可读数据生效的。
		///
		virtual void Flush() override
		{
			throw base::NotSupportedException{};
		}

		///
		/// @brief 关闭流。
		///
		/// @note 关闭后对流的操作将会引发异常。
		///
		virtual void Close() override
		{
		}

		/* #endregion */
	};
} // namespace base
