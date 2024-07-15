#pragma once
#ifndef HAS_THREAD
#define HAS_THREAD 0
#endif

#if HAS_THREAD

#include <base/stream/Stream.h>
#include <base/string/define.h>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace base
{
	class FileStream
		: public base::Stream
	{
	private:
		FileStream(std::string url)
		{
			_url = url;
		}

		std::string _url;
		std::shared_ptr<std::fstream> _fs;
		bool _can_read = false;
		bool _can_write = false;
		bool _can_seek = false;

	public:
		~FileStream()
		{
			Close();
		}

#pragma region 工厂函数
		/// <summary>
		///		用创建模式打开文件流，无论如何都会创建一个新的空白文件。会覆盖旧的。
		/// </summary>
		/// <param name="url">文件路径</param>
		/// <returns>创建文件成功则返回 FileStream 对象。创建失败会抛出异常，不会返回空指针。</returns>
		/// <exception cref="Exception">创建失败会抛出异常。</exception>
		static std::shared_ptr<FileStream> CreateNewAnyway(std::string url);

		/// <summary>
		///		用打开模式打开一个文件。如果文件不存在，此函数不会创建文件。
		/// </summary>
		/// <param name="url">文件路径</param>
		/// <returns>如果文件存在，且成功打开，则返回 FileStream 对象。失败会抛出异常，不会返回空指针。</returns>
		/// <exception cref="Exception">
		///		* 如果文件不存在，会引发异常。
		///		* 如果传进来的 url 不是文件，而是目录，会引发异常
		/// </exception>
		static std::shared_ptr<FileStream> Open(std::string url);

		static std::shared_ptr<FileStream> OpenReadOnly(std::string url);
#pragma endregion

		bool CanRead() override;
		bool CanWrite() override;
		bool CanSeek() override;

		int64_t Length() override;
		void SetLength(int64_t value) override;

		int32_t Read(uint8_t *buffer, int32_t offset, int32_t count) override;
		void Write(uint8_t const *buffer, int32_t offset, int32_t count) override;

		int64_t Position() override;
		void SetPosition(int64_t value) override;

		void Flush() override;
		void Close() override;
	};
}

#endif // HAS_THREAD
