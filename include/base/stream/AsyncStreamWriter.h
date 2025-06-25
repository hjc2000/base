#pragma once
#include "base/IDisposable.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include "base/stream/Stream.h"
#include "base/string/define.h"
#include "base/string/TextWriter.h"
#include "base/task/task.h"
#include "BlockingCircleBufferMemoryStream.h"
#include <atomic>
#include <cstdint>
#include <memory>
#include <stdexcept>

namespace base
{
	///
	/// @brief 异步的流写入器。
	///
	///
	class AsyncStreamWriter final :
		public base::TextWriter,
		public base::IDisposable
	{
	private:
		std::shared_ptr<base::BlockingCircleBufferMemoryStream> _buffer_stream;
		std::shared_ptr<base::Stream> _stream;
		std::shared_ptr<base::task::ITask> _completion_signal;
		std::atomic_bool _disposed = false;
		uint8_t _copy_temp_buffer[1024];

		void ThreadFunc()
		{
			while (true)
			{
				if (_disposed)
				{
					return;
				}

				int32_t have_read = _buffer_stream->Read(base::Span{_copy_temp_buffer, sizeof(_copy_temp_buffer)});
				_stream->Write(base::ReadOnlySpan{_copy_temp_buffer, have_read});
			}
		}

	public:
		AsyncStreamWriter(int32_t max_buffer_size,
						  std::shared_ptr<base::Stream> const &stream)
			: _stream(stream)
		{
			if (stream == nullptr)
			{
				throw std::invalid_argument{CODE_POS_STR + "stream 不能传入空指针。"};
			}

			_buffer_stream = std::shared_ptr<base::BlockingCircleBufferMemoryStream>{new base::BlockingCircleBufferMemoryStream{max_buffer_size}};

			_completion_signal = base::task::run([this]()
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
			_completion_signal->Wait();
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
