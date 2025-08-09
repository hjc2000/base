#pragma once
#include "base/container/Range.h"
#include "base/exception/NotSupportedException.h"
#include "base/stream/Span.h"
#include "base/stream/Stream.h"
#include "base/string/define.h"
#include <algorithm>
#include <cstdint>
#include <stdexcept>

namespace base
{
	class StreamWindow :
		public base::Stream
	{
	private:
		base::Stream *_stream = nullptr;
		base::Range _range{};

	public:
		StreamWindow() = default;

		StreamWindow(base::Stream &stream, base::Range const &range)
		{
			_stream = &stream;
			_range = range;

			_stream->SetPosition(_range.Begin());
		}

		/* #region 接口 - 流属性 */

		///
		/// @brief 本流能否读取。
		///
		/// @return
		///
		virtual bool CanRead() const override
		{
			return _stream->CanRead();
		}

		///
		/// @brief 本流能否写入。
		///
		/// @return
		///
		virtual bool CanWrite() const override
		{
			return _stream->CanWrite();
		}

		///
		/// @brief 本流能否定位。
		///
		/// @return
		///
		virtual bool CanSeek() const override
		{
			return _stream->CanSeek();
		}

		///
		/// @brief 流的长度
		///
		/// @return
		///
		virtual int64_t Length() const override
		{
			int64_t ret = std::min(_range.Size(), _stream->Length());
			return ret;
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
			return _stream->Position() - _range.Begin();
		}

		///
		/// @brief 设置流当前的位置。
		///
		/// @param value
		///
		virtual void SetPosition(int64_t value) override
		{
			if (value < 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "value 不能 < 0."};
			}

			_stream->SetPosition(value + _range.Begin());
		}

		/* #endregion */

		/* #region 接口 - 读写冲关 */

		///
		/// @brief 将本流的数据读取到 span 中。
		///
		/// @param span
		///
		/// @return
		///
		virtual int64_t Read(base::Span const &span) override
		{
			if (Position() >= _range.Size())
			{
				return 0;
			}

			int64_t remain = _range.Size() - Position();
			base::Span sliced_span = span[base::Range{0, std::min(span.Size(), remain)}];
			return _stream->Read(sliced_span);
		}

		///
		/// @brief 将 span 中的数据写入本流。
		///
		/// @param span
		///
		virtual void Write(base::ReadOnlySpan const &span) override
		{
			if (Position() + span.Size() >= _range.Size())
			{
				throw std::overflow_error{CODE_POS_STR + "写入的数据太多，会发生越界。"};
			}

			_stream->Write(span);
		}

		///
		/// @brief 冲洗流。
		///
		/// @note 对于写入的数据，作用是将其从内部缓冲区转移到底层。
		/// @note 对于内部的可以读取但尚未读取的数据，一般不会有什么作用。Flush 没见过对可读数据生效的。
		///
		virtual void Flush() override
		{
			_stream->Flush();
		}

		///
		/// @brief 关闭流。
		///
		/// @note 关闭后流无法写入，写入会引发异常。
		///
		/// @note 关闭后流的读取不会引发异常，但是在读完内部残留的数据后，将不会再读到
		/// 任何数据。
		///
		virtual void Close() override
		{
			_stream->Close();
		}

		/* #endregion */
	};

} // namespace base
