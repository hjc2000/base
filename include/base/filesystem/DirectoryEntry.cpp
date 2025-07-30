#include "DirectoryEntry.h"
#include "base/filesystem/filesystem.h"

base::DirectoryEntry::DirectoryEntry(base::Path const &path)
	: _path(path)
{
}

bool base::DirectoryEntry::Exists() const
{
	return base::filesystem::Exists(_path);
}

/* #region 访问权限 */

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

/* #endregion */

/* #region 类型判断 */

bool base::DirectoryEntry::IsDirectory() const
{
	return base::filesystem::IsDirectory(_path);
}

bool base::DirectoryEntry::IsRegularFile() const
{
	return base::filesystem::IsRegularFile(_path);
}

bool base::DirectoryEntry::IsSymbolicLink() const
{
	return base::filesystem::IsSymbolicLink(_path);
}

/* #endregion */
