#pragma once
#include "base/exception/NotSupportedException.h"
#include "base/math/Counter.h"
#include "base/stream/Stream.h"
#include <cstdint>
#include <memory>

namespace base
{
	///
	/// @brief 具有循环缓冲区的流
	///
	class CircleBufferMemoryStream final :
		public base::Stream
	{
	private:
		std::unique_ptr<uint8_t[]> _buffer{};
		int64_t _buffer_size = 0;

		///
		/// @brief 头部。读取的时候递增头部。头部指向的位置是有效元素。（前提是缓冲区不为空）
		///
		base::Counter<uint64_t> _start;

		///
		/// @brief 尾部
		///
		/// @note 写入的时候递增尾部。尾部指向的位置是无效元素。
		///	 	  尾部 - 1 才是指向有效元素。（前提是缓冲区不为空）
		///
		base::Counter<uint64_t> _end;

		///
		/// @brief 队列是否已满。当头指针和尾指针重叠时，有 2 种情况：
		/// 	@li 缓冲区为空
		/// 	@li 缓冲区满
		///
		/// 此字段用来区分这两种情况。
		///
		bool _is_full = false;

		///
		/// @brief 以非环绕方式读取。
		///
		///	@warning 从 _start 处开始读取 span，不管会不会超出边界，所以调用本方法前需要检查。
		///
		/// @param span
		///
		/// @return
		///
		void ReadNonCircular(base::Span const &span)
		{
			std::copy(_buffer.get() + _start.Value(),
					  _buffer.get() + _start.Value() + span.Size(),
					  span.Buffer());

			_start += span.Size();
			_is_full = false;
		}

		///
		/// @brief 以非环绕方式写入。
		///
		/// @warning 从 _end 处开始往后写入 span，不会管会不会超出边界，所以调用本方法前需要检查。
		///
		/// @param span
		///
		void WriteNonCircular(base::ReadOnlySpan const &span)
		{
			std::copy(span.Buffer(),
					  span.Buffer() + span.Size(),
					  _buffer.get() + _end.Value());

			_end += span.Size();
			_is_full = _start == _end;
		}

		///
		/// @brief 本流为空。
		///
		/// @return
		///
		bool Empty() const
		{
			return _start == _end && !_is_full;
		}

	public:
		///
		/// @brief 构造具有循环缓冲区的流。
		///
		/// @param buffer_size 循环缓冲区的大小。
		///
		CircleBufferMemoryStream(int64_t buffer_size)
			: _start(0, buffer_size - 1),
			  _end(0, buffer_size - 1)

		{
			if (buffer_size < 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "buffer_size 不能小于 0。"};
			}

			_buffer_size = buffer_size;
			_is_full = false;
			_buffer = std::unique_ptr<uint8_t[]>{new uint8_t[buffer_size]};
		}

		///
		/// @brief 返回内部循环缓冲区的大小，也是此流所能达到的最大长度。
		///
		/// @return
		///
		int64_t BufferSize() const
		{
			return _buffer_size;
		}

		///
		/// @brief 本流内部的缓冲区剩余空间。单位：字节。
		///
		/// @return
		///
		int64_t AvailableToWrite() const
		{
			return _buffer_size - Length();
		}

		///
		/// @brief 清空流
		///
		void Clear()
		{
			_start.Reset();
			_end.Reset();
			_is_full = false;
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
			// 循环队列通常不支持随机访问
			return false;
		}

		///
		/// @brief 流的长度
		///
		/// @return
		///
		virtual int64_t Length() const override
		{
			if (_is_full)
			{
				return _buffer_size;
			}

			return _end - _start;
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
			throw base::NotSupportedException{};
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
		virtual int64_t Read(base::Span const &span) override
		{
			if (span.Buffer() == nullptr)
			{
				throw std::invalid_argument{"span 的缓冲区不能是空指针"};
			}

			if (span.Size() == 0)
			{
				throw std::invalid_argument{"span 的大小不能是 0 个字节。"};
			}

			if (Empty())
			{
				// 缓冲区为空
				return 0;
			}

			// span 如果太大，本流的数据无法充满他，所以需要将 span 切片，最大只能到 Length.
			// 如果 span 的大小本来就小于 Length 了，则保持原大小。
			base::Span const should_read_span = span.Slice(base::Range{0, std::min<int64_t>(span.Size(), Length())});
			if (_end > _start)
			{
				// 尾指针在头指针的后面，当前缓冲区内的数据没有环绕，所以读取时也不需要环绕
				ReadNonCircular(should_read_span);
				return should_read_span.Size();
			}

			// 执行到这里说明 _end <= _head，此时缓冲区内的数据发生了环绕，所以读取时有可能要环绕。
			if (should_read_span.Size() <= _buffer_size - static_cast<int64_t>(_start.Value()))
			{
				// 此时从 _start 到缓冲区末尾的数据刚好够本次读取，不用环绕
				ReadNonCircular(should_read_span);
				return should_read_span.Size();
			}

			// 执行到这里说明要环绕了。
			// 先读取从 _start 开始到缓冲区末尾的数据。因为这部分可以先用非环绕的方式读出来。
			base::Span span1 = should_read_span.Slice(base::Range{0, _buffer_size - static_cast<int64_t>(_start.Value())});
			ReadNonCircular(span1);

			// 此时变成非环绕模式了，因为刚才的读取让 _start 发生环绕，已经变成 0 了。
			base::Span span2 = should_read_span.Slice(base::Range{span1.Size(), should_read_span.Size()});
			ReadNonCircular(span2);
			return should_read_span.Size();
		}

		///
		/// @brief 将 span 中的数据写入本流。
		///
		/// @param span
		///
		virtual void Write(base::ReadOnlySpan const &span) override
		{
			if (AvailableToWrite() < span.Size())
			{
				throw std::overflow_error{"缓冲区剩余空间无法接受这么多数据"};
			}

			if (span.Size() <= _buffer_size - static_cast<int64_t>(_end.Value()))
			{
				// _end 到缓冲区尾部的空间刚好够写入，此时不需要环绕
				WriteNonCircular(span);
				return;
			}

			// 需要环绕
			base::ReadOnlySpan span1 = span.Slice(base::Range{0, _buffer_size - static_cast<int64_t>(_end.Value())});
			WriteNonCircular(span1);

			// 此时 _end 已经变成 0 了，继续用 WriteNonCircular 写入剩余的字节
			base::ReadOnlySpan span2 = span.Slice(base::Range{span1.Size(), span.Size()});
			WriteNonCircular(span2);
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
	};

} // namespace base
