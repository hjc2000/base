#include "DirectoryEntry.h"
#include "base/file/filesystem.h"

base::DirectoryEntry::DirectoryEntry(base::Path const &path)
	: _path(path)
{
}

bool base::DirectoryEntry::Exists() const
{
	return base::filesystem::Exists(_path);
}

bool base::DirectoryEntry::IsReadable() const
{
	return base::filesystem::IsReadable(_path);
}

bool base::DirectoryEntry::IsWriteable() const
{
	return base::filesystem::IsWriteable(_path);
}

bool base::DirectoryEntry::IsExcuteable() const
{
	return base::filesystem::IsExcuteable(_path);
}

bool base::DirectoryEntry::IsDirectory() const
{
	return base::filesystem::IsDirectory(_path);
}

bool base::DirectoryEntry::IsRegularFile() const
{
	return base::filesystem::IsRegularFile(_path);
}
