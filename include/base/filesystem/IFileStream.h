#pragma once
#include "base/stream/Stream.h"
#include "Path.h"
#include <memory>

namespace base
{
	///
	/// @brief 文件流接口。
	///
	class IFileStream :
		public base::Stream
	{
	public:
		virtual ~IFileStream() = default;

		/* #region 流属性 */

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

		/* #region 读写冲关 */

		///
		/// @brief 将本流的数据读取到 span 中。
		///
		/// @param span
		///
		/// @return
		///
		virtual int32_t Read(base::Span const &span) = 0;

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
		/// @note 关闭后对流的操作将会引发异常。
		///
		virtual void Close() = 0;
		/* #endregion */
	};

	namespace file
	{
		///
		/// @brief 先尝试打开文件。如果不存在会创建。
		///
		/// @param path
		///
		/// @return
		///
		std::shared_ptr<base::IFileStream> OpenOrCreate(base::Path const &path);

		///
		/// @brief 以只读方式打开文件。文件必须存在，否则会抛出异常。
		///
		/// @param path 文件的路径。
		///
		/// @return 成功打开则返回 base::IFileStream 对象。失败会抛出异常，不会返回空指针。
		///
		std::shared_ptr<base::IFileStream> OpenReadOnly(base::Path const &path);

		///
		/// @brief 用打开模式打开一个存在的文件。如果文件不存在，此函数不会创建文件。
		///
		/// @param path 文件路径
		///
		/// @return 如果文件存在，且成功打开，则返回 base::IFileStream 对象。
		/// 失败会抛出异常，不会返回空指针。
		///
		std::shared_ptr<base::IFileStream> OpenExisting(base::Path const &path);

		///
		/// @brief 用创建模式打开文件流，无论如何都会创建一个新的空白文件。会覆盖旧的。
		///
		/// @param path 文件路径。
		///
		/// @return 创建文件成功则返回 base::IFileStream 对象。创建失败会抛出异常，不会返回空指针。
		///
		std::shared_ptr<base::IFileStream> CreateNewAnyway(base::Path const &path);

	} // namespace file
} // namespace base
