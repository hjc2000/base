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
		///
		/// @brief 根据路径构造一个目录条目。
		///
		/// @param path
		///
		DirectoryEntry(base::Path const &path);

		///
		/// @brief 本条目在文件系统中是否真实存在。
		///
		/// @return true
		/// @return false
		///
		bool Exists() const;

		///
		/// @brief 本条目是否可读。
		///
		/// @return true
		/// @return false
		///
		bool IsReadable() const;

		///
		/// @brief 本条目是否可写。
		///
		/// @return true
		/// @return false
		///
		bool IsWriteable() const;

		///
		/// @brief 本条目是否可执行。
		///
		/// @return true
		/// @return false
		///
		bool IsExcuteable() const;

		///
		/// @brief 检查本条目是否是目录。
		///
		/// @return true
		/// @return false
		///
		bool IsDirectory() const;

		bool IsRegularFile() const;
	};
} // namespace base
