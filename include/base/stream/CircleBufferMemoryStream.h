#pragma once
#include <algorithm>
#include <base/stream/Stream.h>
#include <cstdint>
#include <cstring>
#include <memory>
#include <stdexcept>

namespace base
{
	/// @brief 具有循环缓冲区的流
	class CircleBufferMemoryStream final :
		public base::Stream
	{
	private:
		std::unique_ptr<uint8_t[]> _buffer;
		int32_t _buffer_size;

		/// @brief 头部。读取的时候递增头部。头部指向的位置是有效元素。（前提是缓冲区不为空）
		int32_t _start;

		/// @brief 尾部
		/// @note 写入的时候递增尾部。尾部指向的位置是无效元素。
		///	 	  尾部 - 1 才是指向有效元素。（前提是缓冲区不为空）
		int32_t _end;

		/// @brief 队列是否已满。当头指针和尾指针重叠时，有 2 种情况：
		/// @li 缓冲区为空
		/// @li 缓冲区满
		/// 此字段用来区分这两种情况。
		bool _is_full;

		void AddHead(int32_t value);
		void AddTail(int32_t value);

		int32_t ReadNonCircular(uint8_t *buffer, int32_t offset, int32_t count);
		void WriteNonCircular(uint8_t const *buffer, int32_t offset, int32_t count);

		/// @brief 本流为空。
		/// @return
		bool Empty() const
		{
			return _start == _end && !_is_full;
		}

	public:
		CircleBufferMemoryStream(int32_t size);

		/// @brief 返回内部缓冲区的大小，也是此流所能达到的最大长度。
		/// @return
		int32_t MaxSize() const
		{
			return _buffer_size;
		}

		/// @brief 本流内部的缓冲区剩余空间。单位：字节。
		/// @return
		int32_t AvailableToWrite() const;

		/// @brief 清空流
		void Clear();

#pragma region Stream
		bool CanRead() override;
		bool CanWrite() override;
		bool CanSeek() override;

		/// @brief 流中当前剩余的有效的，可读的字节数。
		/// @return
		int64_t Length() override;

		/// @brief 不支持的操作。调用将引发异常。
		/// @param value
		void SetLength(int64_t value) override;

		virtual int32_t Read(base::Span const &span) override;
		virtual void Write(base::ReadOnlySpan const &span) override;

		/// @brief 调用后什么都不会发生。这是一个空的函数。
		void Flush() override
		{
		}

		/// @brief 没有任何作用
		void Close() override
		{
		}

		/// @brief 调用将发生 std::runtime_error
		/// @return
		int64_t Position() override;

		/// @brief 调用将发生 std::runtime_error
		/// @param value
		void SetPosition(int64_t value) override;
#pragma endregion
	};
} // namespace base
