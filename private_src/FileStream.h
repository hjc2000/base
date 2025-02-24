#pragma once
#if HAS_THREAD

	#include <base/define.h>
	#include <base/stream/IFileStream.h>
	#include <base/string/define.h>
	#include <fstream>

namespace base
{
	class FileStream final :
		public base::IFileStream
	{
	private:
		FileStream(std::string path)
		{
			_path = path;
		}

		std::string _path;
		std::shared_ptr<std::fstream> _fs;
		bool _can_read = false;
		bool _can_write = false;
		bool _can_seek = false;

	public:
		~FileStream()
		{
			Close();
		}

		/// @brief 用创建模式打开文件流，无论如何都会创建一个新的空白文件。会覆盖旧的。
		/// @param path 文件路径
		/// @return 创建文件成功则返回 FileStream 对象。创建失败会抛出异常，不会返回空指针。
		static_function std::shared_ptr<FileStream> CreateNewAnyway(std::string path);

		/// @brief 用打开模式打开一个存在的文件。如果文件不存在，此函数不会创建文件。
		/// @param path 文件路径
		/// @return 如果文件存在，且成功打开，则返回 FileStream 对象。失败会抛出异常，不会返回空指针。
		static_function std::shared_ptr<FileStream> OpenExisting(std::string path);

		/// @brief 以只读方式打开文件。
		/// @param path 文件的路径。
		/// @return 成功打开则返回 FileStream 对象。失败会抛出异常，不会返回空指针。
		static_function std::shared_ptr<FileStream> OpenReadOnly(std::string path);

		bool CanRead() const override;
		bool CanWrite() const override;
		bool CanSeek() const override;

		int64_t Length() const override;
		void SetLength(int64_t value) override;

		virtual int32_t Read(base::Span const &span) override;
		virtual void Write(base::ReadOnlySpan const &span) override;

		int64_t Position() const override;
		void SetPosition(int64_t value) override;

		void Flush() override;
		void Close() override;
	};
} // namespace base

#endif // HAS_THREAD
