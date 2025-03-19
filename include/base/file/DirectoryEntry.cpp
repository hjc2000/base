#include "DirectoryEntry.h"
#include "base/file/filesystem.h"

bool base::DirectoryEntry::IsReadable() const
{
	return base::filesystem::IsReadable(_path);
}

bool base::DirectoryEntry::IsDirectory() const
{
	return base::filesystem::IsDirectory(_path);
}
