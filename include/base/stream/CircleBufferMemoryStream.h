#pragma once
#include "base/stream/Stream.h"
#include <cstdint>
#include <cstring>
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
		std::unique_ptr<uint8_t[]> _buffer;
		int32_t _buffer_size;

		///
		/// @brief 头部。读取的时候递增头部。头部指向的位置是有效元素。（前提是缓冲区不为空）
		///
		int32_t _start;

		///
		/// @brief 尾部
		///
		/// @note 写入的时候递增尾部。尾部指向的位置是无效元素。
		///	 	  尾部 - 1 才是指向有效元素。（前提是缓冲区不为空）
		///
		int32_t _end;

		///
		/// @brief 队列是否已满。当头指针和尾指针重叠时，有 2 种情况：
		/// 	@li 缓冲区为空
		/// 	@li 缓冲区满
		///
		/// 此字段用来区分这两种情况。
		///
		bool _is_full;

		///
		/// @brief 递增头指针。
		///
		/// @param value
		///
		void AddHead(int32_t value);

		///
		/// @brief 递增尾指针。
		///
		/// @param value
		///
		void AddTail(int32_t value);

		///
		/// @brief 以非环绕方式读取。
		///
		///	@warning 从 _start 处开始读取 span，不管会不会超出边界，所以调用本方法前需要检查。
		///
		/// @param span
		///
		/// @return
		///
		void ReadNonCircular(base::Span const &span);

		///
		/// @brief 以非环绕方式写入。
		///
		/// @warning 从 _end 处开始往后写入 span，不会管会不会超出边界，所以调用本方法前需要检查。
		///
		/// @param span
		///
		void WriteNonCircular(base::ReadOnlySpan const &span);

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
		CircleBufferMemoryStream(int32_t buffer_size);

		///
		/// @brief 返回内部循环缓冲区的大小，也是此流所能达到的最大长度。
		///
		/// @return
		///
		int32_t BufferSize() const
		{
			return _buffer_size;
		}

		///
		/// @brief 本流内部的缓冲区剩余空间。单位：字节。
		///
		/// @return
		///
		int32_t AvailableToWrite() const;

		///
		/// @brief 清空流
		///
		void Clear();

		/* #region 流属性 */

		///
		/// @brief 本流能否读取。
		///
		/// @return true 能读取。
		/// @return false 不能读取。
		///
		virtual bool CanRead() const override;

		///
		/// @brief 本流能否写入。
		///
		/// @return true 能写入。
		/// @return false 不能写入。
		///
		virtual bool CanWrite() const override;

		///
		/// @brief 本流能否定位。
		///
		/// @return true 能定位。
		/// @return false 不能定位。
		///
		virtual bool CanSeek() const override;

		///
		/// @brief 流的长度
		///
		/// @return int64_t
		///
		virtual int64_t Length() const override;

		///
		/// @brief 设置流的长度。
		///
		/// @param value
		///
		virtual void SetLength(int64_t value) override;

		///
		/// @brief 流当前的位置。
		///
		/// @return int64_t
		///
		virtual int64_t Position() const override;

		///
		/// @brief 设置流当前的位置。
		///
		/// @param value
		///
		virtual void SetPosition(int64_t value) override;

		/* #endregion */

		/* #region 读写冲关 */

		///
		/// @brief 将本流的数据读取到 span 中。
		///
		/// @param span
		/// @return int32_t
		///
		virtual int32_t Read(base::Span const &span) override;

		///
		/// @brief 将 span 中的数据写入本流。
		///
		/// @param span
		///
		virtual void Write(base::ReadOnlySpan const &span) override;

		///
		/// @brief 冲洗流。
		///
		/// @note 对于写入的数据，作用是将其从内部缓冲区转移到底层。
		/// @note 对于内部的可以读取但尚未读取的数据，一般不会有什么作用。Flush 没见过对可读数据生效的。
		///
		virtual void Flush() override;

		///
		/// @brief 关闭流。
		///
		/// @note 关闭后对流的操作将会引发异常。
		///
		virtual void Close() override;

		/* #endregion */
	};
} // namespace base
