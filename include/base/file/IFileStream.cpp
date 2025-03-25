#include "IFileStream.h"
#include <FileStream.h>

#if HAS_THREAD

std::shared_ptr<base::IFileStream> base::file::OpenReadOnly(base::Path const &path)
{
	return base::FileStream::OpenReadOnly(path.ToString());
}

std::shared_ptr<base::IFileStream> base::file::OpenExisting(base::Path const &path)
{
	return base::FileStream::OpenExisting(path.ToString());
}

std::shared_ptr<base::IFileStream> base::file::CreateNewAnyway(base::Path const &path)
{
	return base::FileStream::CreateNewAnyway(path.ToString());
}

#endif
