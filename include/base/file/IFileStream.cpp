#include "IFileStream.h"
#include <FileStream.h>

#if HAS_THREAD

std::shared_ptr<base::IFileStream> base::file::OpenReadOnly(std::string const &path)
{
	return base::FileStream::OpenReadOnly(path);
}

std::shared_ptr<base::IFileStream> base::file::OpenExisting(std::string const &path)
{
	return base::FileStream::OpenExisting(path);
}

std::shared_ptr<base::IFileStream> base::file::CreateNewAnyway(std::string const &path)
{
	return base::FileStream::CreateNewAnyway(path);
}

#endif
