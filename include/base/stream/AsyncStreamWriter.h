#pragma once
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include "base/stream/Stream.h"
#include "base/string/define.h"
#include "base/string/TextWriter.h"
#include "base/task/task.h"
#include "BlockingCircleBufferMemoryStream.h"
#include <atomic>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <stdexcept>

namespace base
{
	///
	/// @brief 异步的流写入器。
	///
	class AsyncStreamWriter final :
		public base::TextWriter
	{
	private:
		std::shared_ptr<base::BlockingCircleBufferMemoryStream> _buffer_stream;
		std::shared_ptr<base::Stream> _stream;
		std::shared_ptr<base::task::ITask> _thread_exit_signal;
		std::atomic_bool _disposed = false;
		uint8_t _copy_temp_buffer[1024];

		void Initialize(int64_t max_buffer_size,
						std::shared_ptr<base::Stream> const &stream)
		{
			if (stream == nullptr)
			{
				throw std::invalid_argument{CODE_POS_STR + "stream 不能传入空指针。"};
			}

			_stream = stream;
			_buffer_stream = std::shared_ptr<base::BlockingCircleBufferMemoryStream>{new base::BlockingCircleBufferMemoryStream{max_buffer_size}};
		}

		void ThreadFunc()
		{
			while (true)
			{
				// 不需要检查 _disposed 为 true 后返回。只管读取 _buffer_stream 就行了，
				// 在释放阶段，_buffer_stream 会被关闭，在读出残留数据后 Read 方法会返回 0,
				// 此时就可以退出线程了。
				//
				// 如果检查 _buffer_stream 为 true 直接退出，会导致残留数据没被读取。
				int64_t have_read = _buffer_stream->Read(base::Span{_copy_temp_buffer, sizeof(_copy_temp_buffer)});

				if (have_read == 0)
				{
					return;
				}

				_stream->Write(base::ReadOnlySpan{_copy_temp_buffer, have_read});
			}
		}

	public:
		AsyncStreamWriter(int64_t max_buffer_size,
						  std::shared_ptr<base::Stream> const &stream)
		{
			Initialize(max_buffer_size, stream);

			_thread_exit_signal = base::task::run([this]()
												  {
													  ThreadFunc();
												  });
		}

		AsyncStreamWriter(int64_t max_buffer_size,
						  std::shared_ptr<base::Stream> const &stream,
						  size_t thread_stack_size)
		{
			Initialize(max_buffer_size, stream);

			_thread_exit_signal = base::task::run(thread_stack_size,
												  [this]()
												  {
													  ThreadFunc();
												  });
		}

		~AsyncStreamWriter()
		{
			Dispose();
		}

		///
		/// @brief 主动释放对象，让对象不再能够工作。
		///
		///
		virtual void Dispose() override
		{
			if (_disposed)
			{
				return;
			}

			_disposed = true;

			_buffer_stream->Close();
			_thread_exit_signal->Wait();

			// 先等待线程退出，保证 _buffer_stream 中残留的数据都被读出来写到 _stream
			// 中了再关闭 _stream.
			_stream->Close();
		}

		std::shared_ptr<base::Stream> Stream() const
		{
			return _stream;
		}

		///
		/// @brief 将 base::ReadOnlySpan 写入流。
		///
		/// @param span
		///
		virtual void Write(base::ReadOnlySpan const &span) override
		{
			_buffer_stream->Write(span);
		}

		using base::TextWriter::Write;
		using base::TextWriter::WriteLine;
	};

} // namespace base
