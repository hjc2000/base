#include "IFileStream.h"
#include <FileStream.h>

#if HAS_THREAD

std::shared_ptr<base::IFileStream> base::di::filesystem::OpenReadOnly(std::string url)
{
	return base::FileStream::OpenReadOnly(url);
}

std::shared_ptr<base::IFileStream> base::di::filesystem::OpenExisting(std::string url)
{
	return base::FileStream::OpenExisting(url);
}

std::shared_ptr<base::IFileStream> base::di::filesystem::CreateNewAnyway(std::string url)
{
	return base::FileStream::CreateNewAnyway(url);
}

#endif
