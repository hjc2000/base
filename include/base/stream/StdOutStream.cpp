#include "StdOutStream.h" // IWYU pragma: keep
#include "base/exception/NotSupportedException.h"
#include "base/RentedPtrFactory.h"

#if HAS_THREAD

namespace
{
	class StdOutStream :
		public base::Stream
	{
	public:
		/* #region 流属性 */

		///
		/// @brief 本流能否读取。
		///
		/// @return
		///
		virtual bool CanRead() const override
		{
			return false;
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
			return false;
		}

		///
		/// @brief 流的长度
		///
		/// @return
		///
		virtual int64_t Length() const override
		{
			throw base::NotSupportedException{};
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
		/// @return
		///
		virtual int64_t Read(base::Span const &span) override
		{
			throw base::NotSupportedException{};
		}

		///
		/// @brief 将 span 中的数据写入本流。
		///
		/// @param span
		///
		virtual void Write(base::ReadOnlySpan const &span) override
		{
			std::cout.write(reinterpret_cast<char const *>(span.Buffer()), span.Size());
		}

		///
		/// @brief 冲洗流。
		///
		/// @note 对于写入的数据，作用是将其从内部缓冲区转移到底层。
		/// @note 对于内部的可以读取但尚未读取的数据，一般不会有什么作用。Flush 没见过对可读数据生效的。
		///
		virtual void Flush() override
		{
			std::cout.flush();
		}

		///
		/// @brief 关闭流。
		///
		/// @note 关闭后对流的操作将会引发异常。
		///
		virtual void Close() override
		{
			// 标准输出流不能关闭。
		}

		/* #endregion */
	};

	StdOutStream _std_out_stream{};

} // namespace

std::shared_ptr<base::Stream> base::std_out_stream()
{
	return base::RentedPtrFactory::Create(&_std_out_stream);
}

#endif // HAS_THREAD
