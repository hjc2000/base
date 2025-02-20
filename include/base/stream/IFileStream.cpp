#include "IFileStream.h"
#include <FileStream.h>

#if HAS_THREAD

std::shared_ptr<base::IFileStream> base::di::filesystem::OpenReadOnly(std::string const &path)
{
	return base::FileStream::OpenReadOnly(path);
}

std::shared_ptr<base::IFileStream> base::di::filesystem::OpenExisting(std::string const &path)
{
	return base::FileStream::OpenExisting(path);
}

std::shared_ptr<base::IFileStream> base::di::filesystem::CreateNewAnyway(std::string const &path)
{
	return base::FileStream::CreateNewAnyway(path);
}

#endif
