#pragma once
#include "base/IDisposable.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Stream.h"
#include "base/string/define.h"
#include "base/string/TextWriter.h"
#include "BlockingCircleBufferMemoryStream.h"
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
		base::BlockingCircleBufferMemoryStream _buffer_stream{1024 * 4};
		std::shared_ptr<base::Stream> _stream;

	public:
		AsyncStreamWriter(int32_t max_buffer_size,
						  std::shared_ptr<base::Stream> const &stream)
			: _buffer_stream(max_buffer_size),
			  _stream(stream)
		{
			if (_stream == nullptr)
			{
				throw std::invalid_argument{CODE_POS_STR + "stream 不能传入空指针。"};
			}
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
			_stream->Write(span);
		}

		using base::TextWriter::Write;
		using base::TextWriter::WriteLine;
	};

} // namespace base
