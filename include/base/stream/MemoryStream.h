#pragma once
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include "base/stream/Stream.h"
#include "base/string/define.h"
#include <algorithm>
#include <cstdint>
#include <stdexcept>

namespace base
{
	///
	/// @brief 内存流
	///
	class MemoryStream final :
		public base::Stream
	{
	private:
		/* #region BufferContext */

		class BufferContext
		{
		private:
			std::unique_ptr<uint8_t[]> _buffer{};

			/// @brief 引用 _buffer 字段的内存或引用从构造函数中传进来的外部内存。
			/// @note 让本类对象具有引用外部内存的能力，避免拷贝整个缓冲区，可以提高性能。
			base::Span _span{};

		public:
			BufferContext(int64_t max_size)
			{
				if (max_size <= 0)
				{
					throw std::invalid_argument{CODE_POS_STR + "max_size 不能小于等于 0."};
				}

				_buffer = std::unique_ptr<uint8_t[]>{new uint8_t[max_size]};
				_span = base::Span{_buffer.get(), max_size};
			}

			BufferContext(base::Span const &span)
			{
				_span = span;
			}

			base::Span Span() const
			{
				return _span;
			}
		};

		/* #endregion */

		BufferContext _buffer_context;

		///
		/// @brief 指向当前要读或写的位置。Read 和 Write 会操作的第一个字节就是 _position 指向的字节。
		///
		int64_t _position = 0;

		///
		/// @brief 流的长度。
		///
		/// @note 流的长度可以小于缓冲区长度。此标志用来表示流的长度，也是缓冲区中有效数据的长度。
		///
		/// @note 缓冲区中，第 _length 字节是无效的数据。
		/// 	@li 当 _length = 0 时，_buffer[0] 是无效数据，流中没有数据。
		/// 	@li _length 不为 0 时，[0 , _length - 1] 闭区间上是有效数据。
		///
		int64_t _length = 0;

	public:
		///
		/// @brief 此构造函数会在堆上分配一段内存。
		///
		/// @param max_size 内部缓冲区的最大尺寸。小于等于 0 会抛出异常。
		///
		MemoryStream(int64_t max_size)
			: _buffer_context(max_size)
		{
		}

		///
		/// @brief 此构造函数会让本对象引用一段内存，但不持有它。这可以提供流式操作外部内存的途径。
		///
		/// @warning 必须保证本对象生存期内，外部的这段内存始终存活。
		///
		/// @note 引用 span 后不会让流的长度变成 span 的大小。如果 span 中都是有效数据，需要读取的话，
		/// 需要调用 SetLength 方法将流的长度设置为 span 的大小，这样才能读取，否则会认为流中无数据可读。
		///
		/// @param span
		///
		MemoryStream(base::Span const &span)
			: _buffer_context(span)
		{
		}

		///
		/// @brief 获取本流的缓冲区。
		///
		/// @return
		///
		base::Span Span() const
		{
			return _buffer_context.Span();
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
			return true;
		}

		///
		/// @brief 本流能否定位。
		///
		/// @return
		///
		virtual bool CanSeek() const override
		{
			return true;
		}

		///
		/// @brief 流的长度
		///
		/// @return
		///
		virtual int64_t Length() const override
		{
			return _length;
		}

		///
		/// @brief 设置流的长度。
		///
		/// @param value
		///
		virtual void SetLength(int64_t value) override
		{
			if (value > Span().Size())
			{
				throw std::invalid_argument{"value 不能大于缓冲区大小。"};
			}

			_length = value;
			if (_position > _length)
			{
				_position = _length;
			}
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
			if (value > _length)
			{
				throw std::invalid_argument{"value 不能大于流的长度。"};
			}

			_position = value;
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
		virtual int64_t Read(base::Span const &span) override
		{
			if (span.Size() == 0)
			{
				throw std::invalid_argument{"不能读取 0 个字节，因为流读取 0 个字节表示流结束了。"};
			}

			if (Position() == Length())
			{
				return 0;
			}

			int64_t have_read = std::min<int64_t>(Length() - Position(), span.Size());

			std::copy(Span().Buffer() + _position,
					  Span().Buffer() + _position + have_read,
					  span.Buffer());

			_position += have_read;
			return have_read;
		}

		///
		/// @brief 将 span 中的数据写入本流。
		///
		/// @param span
		///
		virtual void Write(base::ReadOnlySpan const &span) override
		{
			if (span.Buffer() == nullptr)
			{
				throw std::invalid_argument{"buffer 不能是空指针。"};
			}

			if (span.Size() > Span().Size() - Position())
			{
				throw std::overflow_error{"缓冲区剩余空间无法接受这么多数据"};
			}

			std::copy(span.Buffer(),
					  span.Buffer() + span.Size(),
					  Span().Buffer() + _position);

			_position += span.Size();
			if (_position > _length)
			{
				// 写完后当前位置超过流的长度，则将流的长度设为当前位置，使流的长度增大。
				_length = _position;
			}
		}

		///
		/// @brief 冲洗流。
		///
		/// @note 对于写入的数据，作用是将其从内部缓冲区转移到底层。
		/// @note 对于内部的可以读取但尚未读取的数据，一般不会有什么作用。Flush 没见过对可读数据生效的。
		///
		virtual void Flush() override
		{
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

		///
		/// @brief 清空流，将 长度和位置都恢复为 0.
		///
		void Clear()
		{
			_position = 0;
			_length = 0;
		}
	};

} // namespace base
