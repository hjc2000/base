#pragma once
#include <base/stream/Stream.h>
#include <stdexcept>

namespace base
{
	class MemoryStream : public base::Stream
	{
	private:
		int32_t _buffer_size;
		uint8_t *_buffer;

		/// <summary>
		///		指向当前要读或写的位置。Read 和 Write 会操作的第一个字节就是 _position 指向的字节。
		/// </summary>
		int32_t _position = 0;

		/// @brief 流的长度。
		/// @note 流的长度可以小于缓冲区长度。此标志用来表示流的长度，也是缓冲区中有效数据的长度。
		/// @note 缓冲区中，第 _length 字节是无效的数据。
		/// 	@li 当 _length = 0 时，_buffer[0] 是无效数据，流中没有数据。
		/// 	@li _length 不为 0 时，[0 , _length - 1] 闭区间上是有效数据。
		int32_t _length = 0;

	public:
		/// @brief
		/// @param max_size 内部缓冲区的最大尺寸。小于等于 0 会抛出异常。
		MemoryStream(int32_t max_size);

		~MemoryStream()
		{
			delete[] _buffer;
		}

		uint8_t *Buffer()
		{
			return _buffer;
		}

		/// @brief 获取内部缓冲区大小。这就是本流能够储存的最大的字节数。
		/// @return
		int32_t BufferSize() const
		{
			return _buffer_size;
		}

		/// @brief 从当前 Position 到 Length，总共有多少个可读字节。
		/// @note 是 Length - Position，不是 max_size - Position，
		/// 	  因为 Length 指向的字节以及后面的字节都是垃圾数据。
		///
		/// @return
		int32_t AvaliableToRead() const
		{
			return _length - _position;
		}

		/// @brief 从当前的 Position 开始，缓冲区中剩余的可写入空间。
		///	@note 不是 Length - Position，而是 max_size - Position。
		///
		/// @return
		int32_t AvaliableToWrite() const
		{
			return _buffer_size - _position;
		}

		bool CanRead() override;

		bool CanWrite() override;

		bool CanSeek() override;

		int64_t Length() override;

		/// @brief
		/// @param value
		/// @exception std::invalid_argument -- value 大于 max_size 会抛出异常。
		void SetLength(int64_t value) override;

		/// @brief
		/// @param buffer
		/// @param offset
		/// @param count
		/// @return
		/// @exception std::invalid_argument -- buffer 为空指针会抛出 std::invalid_argument 异常。
		int32_t Read(uint8_t *buffer, int32_t offset, int32_t count) override;

		/// @brief
		/// @param buffer
		/// @param offset
		/// @param count
		/// @exception std::invalid_argument
		void Write(uint8_t const *buffer, int32_t offset, int32_t count) override;

		void Flush() override;

		/// @brief 没有任何作用。
		void Close() override;

		/// @brief 清空流，将 长度和位置都恢复为 0.
		void Clear()
		{
			_position = 0;
			_length = 0;
		}

		int64_t Position() override;
		void SetPosition(int64_t value) override;
	};
}
