#pragma once
#include "base/file/Path.h"

namespace base
{
	namespace filesystem
	{
		///
		/// @brief 文件存在时的覆盖方式。
		///
		///
		enum class OverwriteOption
		{
			Skip,
			Update,
			Overwrite,
		};

		/* #region 访问权限检查 */

		///
		/// @brief 检查文件或目录是否可读。
		///
		/// @param path
		/// @return true
		/// @return false
		///
		bool IsReadable(base::Path const &path);

		///
		/// @brief 检查文件或目录是否可写。
		///
		/// @param path
		/// @return true
		/// @return false
		///
		bool IsWriteable(base::Path const &path);

		///
		/// @brief 检查文件或目录是否可执行。
		///
		/// @note 对于目录，执行的意思是进入该目录。
		///
		/// @param path
		/// @return true
		/// @return false
		///
		bool IsExcuteable(base::Path const &path);
		/* #endregion */

		/* #region 目标类型检查 */

		///
		/// @brief 检查指定路径是否是一个目录。
		///
		/// @param path
		/// @return true
		/// @return false
		///
		bool IsDirectory(base::Path const &path);

		///
		/// @brief 检查指定路径是否是一个常规的文件。
		///
		/// @note 常规文件是文件系统中储存在磁盘等介质中的数据，不是设备文件或套接字之类的抽象出来
		/// 映射到文件系统中的文件。
		///
		/// @param path
		/// @return true
		/// @return false
		///
		bool IsRegularFile(base::Path const &path);

		///
		/// @brief 是否是广义的文件。
		///
		/// @note 广义的文件包括：符号链接、设备文件、套接字等。
		/// @note 只要不是目录，就是广义的文件。
		///
		/// @param path
		/// @return true
		/// @return false
		///
		inline bool IsFile(base::Path const &path)
		{
			return !IsDirectory(path);
		}

		///
		/// @brief 检查指定路径是否是一个符号链接。
		///
		/// @param path
		/// @return true
		/// @return false
		///
		bool IsSymbolicLink(base::Path const &path);
		/* #endregion */

		///
		/// @brief 检查指定路径是否存在。
		///
		/// @note 不管它是目录还是文件，只要存在就返回 true.
		///
		/// @param path
		/// @return true
		/// @return false
		///
		bool Exists(base::Path const &path);

		///
		/// @brief 读取符号链接指向的路径。
		///
		/// @param path
		/// @return base::Path
		///
		base::Path ReadSymlink(base::Path const &path);

		///
		/// @brief 创建一个目录。
		///
		/// @param path 要创建的目录的路径。
		///
		/// @exception std::runtime_error 目标路径已存在会抛出异常。
		///
		void CreateDirectory(base::Path const &path);

		///
		/// @brief 确保目标路径是一个存在的目录。
		///
		/// @param path
		///
		/// @exception runtime_error 如果目标路径已存在，但不是目录，会抛出异常。
		///
		void EnsureDirectory(base::Path const &path);

		///
		/// @brief 删除目录或文件或符号链接。
		///
		/// @note 删除符号链接是是删除符号链接本身，不会跟踪到符号链接指向的位置去删除。
		///
		/// @param path
		///
		void Remove(base::Path const &path);

		///
		/// @brief 将文件或目录从 source_path 复制到 destination_path.
		///
		/// @note 其中的符号链接本身会被赋值，不会进入到符号链接指向的实际位置去复制文件。
		///
		/// @param source_path
		/// @param destination_path
		/// @param overwrite_method
		///
		/// @exception std::runtime_error 目标路径已存在会抛出异常。
		///
		void Copy(base::Path const &source_path,
				  base::Path const &destination_path,
				  base::filesystem::OverwriteOption overwrite_method);

		///
		/// @brief 将文件或目录从 source_path 移动到 destination_path.
		///
		/// @param source_path
		/// @param destination_path
		///
		/// @exception std::runtime_error 目标路径已存在会抛出异常。
		///
		void Move(base::Path const &source_path,
				  base::Path const &destination_path);

	} // namespace filesystem
} // namespace base
