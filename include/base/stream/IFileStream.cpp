#include "IFileStream.h"
#include <FileStream.h>

void base::IFileStream::Write(std::string const &str)
{
	base::ReadOnlySpan span{
		reinterpret_cast<uint8_t const *>(str.data()),
		static_cast<int32_t>(str.size()),
	};

	Write(span);
}

void base::IFileStream::WriteLine(std::string const &str)
{
	Write(str);
	Write('\n');
}

void base::IFileStream::Write(char c)
{
	base::ReadOnlySpan span{
		reinterpret_cast<uint8_t const *>(&c),
		1,
	};

	Write(span);
}

void base::IFileStream::WriteLine(char c)
{
	Write(c);
	Write('\n');
}

void base::IFileStream::WriteLine()
{
	Write('\n');
}

#if HAS_THREAD

std::shared_ptr<base::IFileStream> base::di::file::OpenReadOnly(std::string const &path)
{
	return base::FileStream::OpenReadOnly(path);
}

std::shared_ptr<base::IFileStream> base::di::file::OpenExisting(std::string const &path)
{
	return base::FileStream::OpenExisting(path);
}

std::shared_ptr<base::IFileStream> base::di::file::CreateNewAnyway(std::string const &path)
{
	return base::FileStream::CreateNewAnyway(path);
}

#endif
