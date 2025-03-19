#pragma once
#include "base/file/Path.h"

namespace base
{
	///
	/// @brief 目录条目。
	///
	/// @note 只要是能放在目录中的条目都是目录条目。例如：目录、符号链接、普通文件、设备文件等。
	///
	///
	class DirectoryEntry
	{
	private:
		base::Path _path;

	public:
		DirectoryEntry(base::Path const &path)
		{
		}

		///
		/// @brief 本条目是否可读。
		///
		/// @return true
		/// @return false
		///
		bool IsReadable() const;

		///
		/// @brief 检查本条目是否是目录。
		///
		/// @return true
		/// @return false
		///
		bool IsDirectory() const;
	};
} // namespace base
