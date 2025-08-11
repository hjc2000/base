#include "file.h"
#include "FileStream.h"

#if HAS_THREAD

std::shared_ptr<base::Stream> base::file::OpenOrCreate(base::Path const &path)
{
	return base::FileStream::OpenOrCreate(path.ToString());
}

std::shared_ptr<base::Stream> base::file::OpenReadOnly(base::Path const &path)
{
	return base::FileStream::OpenReadOnly(path.ToString());
}

std::shared_ptr<base::Stream> base::file::OpenExisting(base::Path const &path)
{
	return base::FileStream::OpenExisting(path.ToString());
}

std::shared_ptr<base::Stream> base::file::CreateNewAnyway(base::Path const &path)
{
	return base::FileStream::CreateNewAnyway(path.ToString());
}

#endif
