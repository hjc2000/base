#pragma once
#include <base/stream/Stream.h>
#include <memory>

namespace base
{
	class IFileStream :
		public base::Stream
	{
	public:
		virtual bool CanRead() const = 0;
		virtual bool CanWrite() const = 0;
		virtual bool CanSeek() const = 0;

		/// @brief 流的长度
		/// @return
		virtual int64_t Length() const = 0;
		virtual void SetLength(int64_t value) = 0;

		/// @brief 将本流的数据读取到 span 中。
		/// @param span
		/// @return
		virtual int32_t Read(base::Span const &span) = 0;

		/// @brief 将 span 中的数据写入本流。
		/// @param span
		virtual void Write(base::ReadOnlySpan const &span) = 0;

		/// @brief 冲洗流
		/// @note 对于写入的数据，作用是将其从内部缓冲区转移到底层。
		/// @note 对于内部的可以读取但尚未读取的数据，一般不会有什么作用。Flush 没见过对可读数据生效的。
		virtual void Flush() = 0;

		/// @brief 关闭流。
		/// @note 关闭后对流的操作将会引发异常。
		virtual void Close() = 0;

		/// @brief 流当前的位置
		/// @return
		virtual int64_t Position() const = 0;
		virtual void SetPosition(int64_t value) = 0;
	};

	namespace di
	{
		namespace filesystem
		{
			/// @brief 以只读方式打开文件。
			/// @param url 文件的路径。
			/// @return 成功打开则返回 base::IFileStream 对象。失败会抛出异常，不会返回空指针。
			std::shared_ptr<base::IFileStream> OpenReadOnly(std::string url);

			/// @brief 用打开模式打开一个存在的文件。如果文件不存在，此函数不会创建文件。
			/// @param url 文件路径
			/// @return 如果文件存在，且成功打开，则返回 base::IFileStream 对象。失败会抛出异常，不会返回空指针。
			std::shared_ptr<base::IFileStream> OpenExisting(std::string url);

			/// @brief 用创建模式打开文件流，无论如何都会创建一个新的空白文件。会覆盖旧的。
			/// @param url 文件路径
			/// @return 创建文件成功则返回 base::IFileStream 对象。创建失败会抛出异常，不会返回空指针。
			std::shared_ptr<base::IFileStream> CreateNewAnyway(std::string url);
		} // namespace filesystem
	} // namespace di
} // namespace base
