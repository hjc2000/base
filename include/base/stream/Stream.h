#pragma once
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include "base/string/define.h"
#include "base/task/CancellationToken.h"
#include <cstdint>
#include <memory>
#include <stdexcept>

namespace base
{
	///
	/// @brief 流接口。
	///
	class Stream
	{
	public:
		virtual ~Stream() = default;

		/* #region 接口 - 流属性 */

		///
		/// @brief 本流能否读取。
		///
		/// @return
		///
		virtual bool CanRead() const = 0;

		///
		/// @brief 本流能否写入。
		///
		/// @return
		///
		virtual bool CanWrite() const = 0;

		///
		/// @brief 本流能否定位。
		///
		/// @return
		///
		virtual bool CanSeek() const = 0;

		///
		/// @brief 流的长度
		///
		/// @return
		///
		virtual int64_t Length() const = 0;

		///
		/// @brief 设置流的长度。
		///
		/// @param value
		///
		virtual void SetLength(int64_t value) = 0;

		///
		/// @brief 流当前的位置。
		///
		/// @return
		///
		virtual int64_t Position() const = 0;

		///
		/// @brief 设置流当前的位置。
		///
		/// @param value
		///
		virtual void SetPosition(int64_t value) = 0;

		/* #endregion */

		/* #region 接口 - 读写冲关 */

		///
		/// @brief 将本流的数据读取到 span 中。
		///
		/// @param span
		///
		/// @return
		///
		virtual int64_t Read(base::Span const &span) = 0;

		///
		/// @brief 将 span 中的数据写入本流。
		///
		/// @param span
		///
		virtual void Write(base::ReadOnlySpan const &span) = 0;

		///
		/// @brief 冲洗流。
		///
		/// @note 对于写入的数据，作用是将其从内部缓冲区转移到底层。
		/// @note 对于内部的可以读取但尚未读取的数据，一般不会有什么作用。Flush 没见过对可读数据生效的。
		///
		virtual void Flush() = 0;

		///
		/// @brief 关闭流。
		///
		/// @note 关闭后流无法写入，写入会引发异常。
		///
		/// @note 关闭后流的读取不会引发异常，但是在读完内部残留的数据后，将不会再读到
		/// 任何数据。
		///
		virtual void Close() = 0;

		/* #endregion */

		/* #region 接口扩展 */

		///
		/// @brief 从流中读取数据写入 buffer。
		///
		/// @param buffer 要将读取到的数据写入的缓冲区。
		/// @param offset 将读取到的数据写入 dst_buf 时的起始位置。
		/// @param count 要读取的字节数。
		///
		/// @return 实际读取的字节数。如果返回 0，说明此流结束。
		///
		int64_t Read(uint8_t *buffer, int64_t offset, int64_t count)
		{
			return Read(base::Span{buffer + offset, count});
		}

		///
		/// @brief 从流中精确读取等于 span 大小的字节数写入 span 中。
		///
		/// @note 如果遇到流末尾，无法满足要求，则读取到的字节数会小于 span 的长度。
		///
		/// @param span
		///
		/// @return 读取了多少字节。
		///
		int64_t ReadExactly(base::Span const &span)
		{
			base::Span remain_span{span};
			while (remain_span.Size() > 0)
			{
				int64_t have_read = Read(remain_span);
				if (have_read == 0)
				{
					// 到达流结尾了，读到多少就多少，直接返回
					break;
				}

				remain_span = remain_span.Slice(base::Range{have_read, remain_span.Size()});
			}

			return span.Size() - remain_span.Size();
		}

		///
		/// @brief 从流中读取精确数量的字节数写入 buffer 中。
		///
		/// @note 如果遇到流末尾，无法满足要求，则读取到的字节数会小于 count。
		///
		/// @param buffer
		/// @param offset
		/// @param count
		///
		/// @return 读取到的字节数。
		/// 	@note 一般等于 count，除非到达流末尾，无法满足要求了。调用者应该检查返回值，
		/// 	判断是否满足要求。
		///
		int64_t ReadExactly(uint8_t *buffer, int64_t offset, int64_t count)
		{
			return ReadExactly(base::Span{buffer + offset, count});
		}

		///
		/// @brief 将 buffer 中的数据写入流中。
		///
		/// @param buffer
		/// @param offset
		/// @param count
		///
		void Write(uint8_t const *buffer, int64_t offset, int64_t count)
		{
			Write(base::ReadOnlySpan{buffer + offset, count});
		}

		/* #endregion */

		/* #region CopyTo */

		///
		/// @brief 将本流拷贝到 dst_stream 中。
		///
		/// @param dst_stream 目标流。
		/// @param temp_buffer_span 拷贝用的临时缓冲区。
		/// @param cancellation_token 取消令牌。
		///
		void CopyTo(std::shared_ptr<base::Stream> dst_stream,
					base::Span const &temp_buffer_span,
					std::shared_ptr<base::CancellationToken> cancellation_token)
		{
			while (true)
			{
				base::throw_if_cancellation_is_requested(cancellation_token);

				int64_t have_read = Read(temp_buffer_span);

				if (have_read == 0)
				{
					return;
				}

				base::ReadOnlySpan have_read_span{
					temp_buffer_span.Buffer(),
					have_read,
				};

				dst_stream->Write(have_read_span);
			}
		}

		///
		/// @brief 将本流拷贝到 dst_stream 中。
		///
		/// @param dst_stream 目标流。
		/// @param temp_buffer 拷贝用的临时缓冲区。
		/// @param temp_buffer_size 临时缓冲区大小。
		/// @param cancellation_token 取消令牌。
		///
		void CopyTo(std::shared_ptr<base::Stream> dst_stream,
					uint8_t *temp_buffer,
					int64_t temp_buffer_size,
					std::shared_ptr<base::CancellationToken> cancellation_token)
		{
			base::Span temp_buffer_span{temp_buffer, temp_buffer_size};
			CopyTo(dst_stream, temp_buffer_span, cancellation_token);
		}

		///
		/// @brief 将本流拷贝到 dst_stream 中。
		///
		/// @param dst_stream 目标流。
		/// @param cancellation_token 取消令牌。
		///
		void CopyTo(std::shared_ptr<base::Stream> dst_stream,
					std::shared_ptr<base::CancellationToken> cancellation_token)
		{
#if HAS_THREAD

			uint8_t temp_buffer[1024];

#else

			uint8_t temp_buffer[32];

#endif

			base::Span temp_buffer_span{temp_buffer, sizeof(temp_buffer)};
			CopyTo(dst_stream, temp_buffer_span, cancellation_token);
		}

		///
		/// @brief 将本流拷贝到 dst_stream 中。
		///
		/// @param dst_stream 目标流。
		///
		/// @param temp_buffer_size 拷贝时使用的临时缓冲区的大小。
		/// 	@note 临时缓冲区会在堆上分配。
		///
		/// @param cancellation_token 取消令牌。
		///
		void CopyTo(std::shared_ptr<base::Stream> dst_stream,
					int64_t temp_buffer_size,
					std::shared_ptr<base::CancellationToken> cancellation_token)
		{
			if (temp_buffer_size <= 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "temp_buffer_size 不能 <= 0."};
			}

			std::unique_ptr<uint8_t[]> temp_buffer{new uint8_t[temp_buffer_size]};
			base::Span temp_buffer_span{temp_buffer.get(), temp_buffer_size};
			CopyTo(dst_stream, temp_buffer_span, cancellation_token);
		}

		/* #endregion */
	};

} // namespace base
