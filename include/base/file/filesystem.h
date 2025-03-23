#pragma once
#include "base/container/iterator/IEnumerable.h"
#include "base/file/Path.h"
#include "DirectoryEntry.h"
#include <memory>

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
		/// @note 不支持通过多层路径直接创建深层目录。
		///
		/// @exception std::runtime_error 目标路径已存在会抛出异常。
		///
		void CreateDirectory(base::Path const &path);

		///
		/// @brief 递归地创建一个目录。
		///
		/// @param path 要创建的目录的路径。
		///
		/// @exception std::runtime_error 目标路径已存在会抛出异常。
		///
		void CreateDirectoryRecursively(base::Path const &path);

		///
		/// @brief 确保目标路径是一个存在的目录。如果目标路径不存在，会创建空目录。
		///
		/// @param path 要确保存在的目录路径。
		/// @note 支持递归创建目录。
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

		/* #region 迭代目录条目 */

		///
		/// @brief 创建目录条目迭代器。
		///
		/// @param path
		/// @return std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>>
		///
		std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> CreateDirectoryEntryEnumerator(base::Path const &path);

		///
		/// @brief 创建目录条目递归迭代器。
		///
		/// @param path
		/// @return std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>>
		///
		std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> CreateDirectoryEntryRecursiveEnumerator(base::Path const &path);

		///
		/// @brief 包装目录条目迭代器。
		///
		///
		class DirectoryEntryEnumerable :
			public base::IEnumerable<base::DirectoryEntry const>
		{
		private:
			std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> _it;

		public:
			DirectoryEntryEnumerable(base::Path const &path)
			{
				_it = CreateDirectoryEntryEnumerator(path);
			}

			///
			/// @brief 获取非 const 迭代器
			///
			/// @return std::shared_ptr<base::IEnumerator<ItemType>>
			///
			virtual std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> GetEnumerator() override
			{
				return _it;
			}
		};

		///
		/// @brief 包装目录条目递归迭代器。
		///
		///
		class RecursiveDirectoryEntryEnumerable :
			public base::IEnumerable<base::DirectoryEntry const>
		{
		private:
			std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> _it;

		public:
			RecursiveDirectoryEntryEnumerable(base::Path const &path)
			{
				_it = CreateDirectoryEntryRecursiveEnumerator(path);
			}

			///
			/// @brief 获取非 const 迭代器
			///
			/// @return std::shared_ptr<base::IEnumerator<ItemType>>
			///
			virtual std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> GetEnumerator() override
			{
				return _it;
			}
		};

		/* #endregion */

	} // namespace filesystem

#if HAS_THREAD
	namespace test
	{
		///
		/// @brief 测试遍历目录条目。
		///
		///
		void TestDirectoryEntryEnumerable();

		///
		/// @brief 测试递归遍历目录条目。
		///
		///
		void TestRecursiveDirectoryEntryEnumerable();
	} // namespace test
#endif // HAS_THREAD

} // namespace base
