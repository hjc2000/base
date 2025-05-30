#pragma once
#include "base/container/Queue.h"
#include "base/delegate/Delegate.h"
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
		std::shared_ptr<base::Stream> TryGetStream();

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
		void AppendStream(std::shared_ptr<base::Stream> stream);

		/* #region 流属性 */

		///
		/// @brief 本流能否读取。
		///
		/// @return true 能读取。
		/// @return false 不能读取。
		///
		virtual bool CanRead() const override;

		///
		/// @brief 本流能否写入。
		///
		/// @return true 能写入。
		/// @return false 不能写入。
		///
		virtual bool CanWrite() const override;

		///
		/// @brief 本流能否定位。
		///
		/// @return true 能定位。
		/// @return false 不能定位。
		///
		virtual bool CanSeek() const override;

		///
		/// @brief 流的长度
		///
		/// @return int64_t
		///
		virtual int64_t Length() const override;

		///
		/// @brief 设置流的长度。
		///
		/// @param value
		///
		virtual void SetLength(int64_t value) override;

		///
		/// @brief 流当前的位置。
		///
		/// @return int64_t
		///
		virtual int64_t Position() const override;

		///
		/// @brief 设置流当前的位置。
		///
		/// @param value
		///
		virtual void SetPosition(int64_t value) override;

		/* #endregion */

		/* #region 读写冲关 */

		///
		/// @brief 将本流的数据读取到 span 中。
		///
		/// @param span
		/// @return int32_t
		///
		virtual int32_t Read(base::Span const &span) override;

		///
		/// @brief 将 span 中的数据写入本流。
		///
		/// @param span
		///
		virtual void Write(base::ReadOnlySpan const &span) override;

		///
		/// @brief 冲洗流。
		///
		/// @note 对于写入的数据，作用是将其从内部缓冲区转移到底层。
		/// @note 对于内部的可以读取但尚未读取的数据，一般不会有什么作用。Flush 没见过对可读数据生效的。
		///
		virtual void Flush() override;

		///
		/// @brief 关闭流。
		///
		/// @note 关闭后对流的操作将会引发异常。
		///
		virtual void Close() override;

		/* #endregion */
	};
} // namespace base
