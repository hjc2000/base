#pragma once
#include <base/container/Queue.h>
#include <base/stream/Stream.h>
#include <functional>
#include <memory>

namespace base
{
	class JoinedStream final :
		public base::Stream
	{
	private:
		/// @brief 用来统计总共从 Read 函数中读取过多少字节。
		int64_t _position = 0;
		Queue<std::shared_ptr<base::Stream>> _stream_queue{};
		std::shared_ptr<base::Stream> _current_stream;

		/// @brief 当前流读到尽头时就会触发此回调。
		/// @note 需要调用 AppendStream 方法添加流到本对象，否则 JoinedStream 将结束。
		std::function<void()> _on_current_stream_end;

		/// @brief 尝试从队列中获取流，如果队列为空，会触发回调然后再尝试退队。如果实在获取不到新的流，
		/// 本方法会返回 nullptr。
		/// @return
		std::shared_ptr<base::Stream> TryGetStream();

	public:
		/// @brief 订阅 CurrentStreamEndEvent. 同时只能有一个函数被回调，多次调用本函数进行
		/// 订阅会覆盖前面的。
		/// @param func
		void SubscribeToCurrentStreamEndEvent(std::function<void()> func);

		/// @brief 向本对象中追加流。如果不追加，在队列中所有流都读完后，JoinedStream 也将结束。
		/// @param stream
		void AppendStream(std::shared_ptr<base::Stream> stream);

#pragma region Stream
		bool CanRead() override;
		bool CanWrite() override;
		bool CanSeek() override;

		int64_t Length() override;
		void SetLength(int64_t value) override;

		int32_t Read(uint8_t *buffer, int32_t offset, int32_t count) override;
		void Write(uint8_t const *buffer, int32_t offset, int32_t count) override;

		void Flush() override;
		void Close() override;

		int64_t Position() override;
		void SetPosition(int64_t value) override;
#pragma endregion
	};
} // namespace base
