#pragma once
#include "base/filesystem/Path.h"

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
		DirectoryEntry() = default;

		///
		/// @brief 根据路径构造一个目录条目。
		///
		/// @param path
		///
		DirectoryEntry(base::Path const &path);

		base::Path const &Path() const
		{
			return _path;
		}

		///
		/// @brief 本条目在文件系统中是否真实存在。
		///
		/// @return true
		/// @return false
		///
		bool Exists() const;

		/* #region 访问权限 */

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

		/* #endregion */

		/* #region 类型判断 */

		///
		/// @brief 检查本条目是否是目录。
		///
		/// @return true
		/// @return false
		///
		bool IsDirectory() const;

		///
		/// @brief 是常规文件。
		///
		/// @note 常规文件是文件系统中储存在磁盘等介质中的数据，不是设备文件或套接字之类的抽象出来
		/// 映射到文件系统中的文件。
		///
		/// @return true
		/// @return false
		///
		bool IsRegularFile() const;

		///
		/// @brief 是广义的文件。
		///
		/// @note 广义的文件包括：符号链接、设备文件、套接字等。
		/// @note 只要不是目录，就是广义的文件。
		///
		/// @return true
		/// @return false
		///
		bool IsFile() const
		{
			return !IsDirectory();
		}

		///
		/// @brief 是符号链接。
		///
		/// @return true
		/// @return false
		///
		bool IsSymbolicLink() const;

		/* #endregion */
	};
} // namespace base
