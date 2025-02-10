#pragma once
#include <base/stream/ReadOnlySpan.h>
#include <base/stream/Span.h>
#include <base/task/CancellationToken.h>
#include <base/task/TaskCanceledException.h>
#include <memory>
#include <stdint.h>

namespace base
{
	/// @brief 流接口。
	class Stream
	{
	public:
		virtual ~Stream() = default;

		virtual bool CanRead() = 0;
		virtual bool CanWrite() = 0;
		virtual bool CanSeek() = 0;

		/// @brief 流的长度
		/// @return
		virtual int64_t Length() = 0;
		virtual void SetLength(int64_t value) = 0;

		/// @brief 将本流的数据读取到 span 中。
		/// @param span
		/// @return
		virtual int32_t Read(base::Span const &span) = 0;

		/// @brief 从流中读取数据写入 buffer。
		/// @param buffer 要将读取到的数据写入的缓冲区。
		/// @param offset 将读取到的数据写入 dst_buf 时的起始位置。
		/// @param count 要读取的字节数。
		/// @return 实际读取的字节数。如果返回 0，说明此流结束。
		int32_t Read(uint8_t *buffer, int32_t offset, int32_t count)
		{
			return Read(base::Span{buffer + offset, count});
		}

		virtual int32_t ReadExactly(base::Span const &span);

		/// @brief 从流中读取精确数量的字节数写入 buffer 中。
		/// 	   如果遇到流末尾，无法满足要求，则读取到的字节数会小于 count。
		///
		/// @param buffer
		/// @param offset
		/// @param count
		///
		/// @return 返回读取到的字节数。
		/// @note 一般等于 count，除非到达流末尾，无法满足要求了。
		/// 	  调用者应该检查返回值，判断是否满足要求。
		int32_t ReadExactly(uint8_t *buffer, int32_t offset, int32_t count)
		{
			return ReadExactly(base::Span{buffer + offset, count});
		}

		virtual void Write(base::ReadOnlySpan const &span) = 0;

		/// @brief 将 buffer 中的数据写入流中。
		/// @param buffer
		/// @param offset
		/// @param count
		void Write(uint8_t const *buffer, int32_t offset, int32_t count)
		{
			Write(base::ReadOnlySpan{buffer + offset, count});
		}

		/// @brief 将本流拷贝到 dst_stream 中。
		/// @param dst_stream
		/// @param cancellationToken
		virtual void CopyTo(std::shared_ptr<base::Stream> dst_stream,
							std::shared_ptr<base::CancellationToken> cancellationToken);

		/// @brief 冲洗流
		/// @note 对于写入的数据，作用是将其从内部缓冲区转移到底层。
		/// @note 对于内部的可以读取但尚未读取的数据，一般不会有什么作用。Flush 没见过对可读数据生效的。
		virtual void Flush() = 0;

		/// @brief 关闭流。
		/// @note 关闭后对流的操作将会引发异常。
		virtual void Close() = 0;

		/// @brief 流当前的位置
		/// @return
		virtual int64_t Position() = 0;
		virtual void SetPosition(int64_t value) = 0;
	};
} // namespace base
