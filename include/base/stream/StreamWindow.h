#pragma once
#include "base/stream/Stream.h"

namespace base
{
	class StreamWindow :
		public base::Stream
	{
	public:
		/* #region 接口 - 流属性 */

		///
		/// @brief 本流能否读取。
		///
		/// @return
		///
		virtual bool CanRead() const override = 0;

		///
		/// @brief 本流能否写入。
		///
		/// @return
		///
		virtual bool CanWrite() const override = 0;

		///
		/// @brief 本流能否定位。
		///
		/// @return
		///
		virtual bool CanSeek() const override = 0;

		///
		/// @brief 流的长度
		///
		/// @return
		///
		virtual int64_t Length() const override = 0;

		///
		/// @brief 设置流的长度。
		///
		/// @param value
		///
		virtual void SetLength(int64_t value) override = 0;

		///
		/// @brief 流当前的位置。
		///
		/// @return
		///
		virtual int64_t Position() const override = 0;

		///
		/// @brief 设置流当前的位置。
		///
		/// @param value
		///
		virtual void SetPosition(int64_t value) override = 0;

		/* #endregion */

		/* #region 接口 - 读写冲关 */

		///
		/// @brief 将本流的数据读取到 span 中。
		///
		/// @param span
		///
		/// @return
		///
		virtual int64_t Read(base::Span const &span) override = 0;

		///
		/// @brief 将 span 中的数据写入本流。
		///
		/// @param span
		///
		virtual void Write(base::ReadOnlySpan const &span) override = 0;

		///
		/// @brief 冲洗流。
		///
		/// @note 对于写入的数据，作用是将其从内部缓冲区转移到底层。
		/// @note 对于内部的可以读取但尚未读取的数据，一般不会有什么作用。Flush 没见过对可读数据生效的。
		///
		virtual void Flush() override = 0;

		///
		/// @brief 关闭流。
		///
		/// @note 关闭后流无法写入，写入会引发异常。
		///
		/// @note 关闭后流的读取不会引发异常，但是在读完内部残留的数据后，将不会再读到
		/// 任何数据。
		///
		virtual void Close() override = 0;

		/* #endregion */
	};

} // namespace base
