#pragma once
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Stream.h"
#include "base/string/define.h"
#include "base/string/TextWriter.h"
#include <stdexcept>

namespace base
{
	///
	/// @brief 向流中写入字符串的工具。
	///
	///
	class StreamWriter :
		public base::TextWriter
	{
	private:
		std::shared_ptr<base::Stream> _stream;

	public:
		StreamWriter(std::shared_ptr<base::Stream> const &stream)
			: _stream(stream)
		{
			if (_stream == nullptr)
			{
				throw std::invalid_argument{CODE_POS_STR + "stream 不能传入空指针。"};
			}
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
