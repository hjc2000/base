#pragma once
#include "base/container/iterator/IEnumerable.h"
#include "base/filesystem/Path.h"
#include <format>
#include <memory>

namespace base::filesystem
{
	///
	/// @brief 文件存在时的覆盖方式。
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
	///
	/// @return 可读返回 true, 否则返回 false.
	///
	bool IsReadable(base::Path const &path);

	///
	/// @brief 检查文件或目录是否可写。
	///
	/// @param path
	///
	/// @return 可写返回 true, 否则返回 false.
	///
	bool IsWriteable(base::Path const &path);

	///
	/// @brief 检查文件或目录是否可执行。
	///
	/// @note 对于目录，执行的意思是进入该目录。
	///
	/// @param path
	///
	/// @return 可执行返回 true, 否则返回 false.
	///
	bool IsExcuteable(base::Path const &path);

	/* #endregion */

	/* #region 目标类型检查 */

	///
	/// @brief 检查指定路径是否是一个目录。
	///
	/// @param path
	///
	/// @return 是目录返回 true, 否则返回 false.
	///
	bool IsDirectory(base::Path const &path);

	///
	/// @brief 检查指定路径是否是一个常规的文件。
	///
	/// @note 常规文件是文件系统中储存在磁盘等介质中的数据，不是设备文件或套接字之类的抽象出来
	/// 映射到文件系统中的文件。
	///
	/// @param path
	///
	/// @return 是常规文件返回 true, 否则返回 false.
	///
	bool IsRegularFile(base::Path const &path);

	///
	/// @brief 检查指定路径是否是一个符号链接。
	///
	/// @param path
	///
	/// @return 是符号链接返回 true, 否则返回 false.
	///
	bool IsSymbolicLink(base::Path const &path);

	///
	/// @brief 是一个符号链接目录。
	///
	/// @note 检查符号链接文件本身的属性中是不是指示该符号链接应该链接一个目录。
	///
	/// @note windows 的傻逼设计，符号链接分成 2 种类型，不兼容的，一种是文件的
	/// 符号链接，一种是目录的符号链接。
	///
	/// @param path
	///
	/// @return
	///
	bool IsSymbolicLinkDirectory(base::Path const &path);

	/* #endregion */

	///
	/// @brief 获取当前路径。
	///
	/// @return
	///
	base::Path CurrentPath();

	///
	/// @brief 通过当前路径和字符串处理计算出绝对路径。
	///
	/// @warning 得到的路径不一定真实存在，需要自行检查。
	///
	/// @param path
	/// @return
	///
	inline base::Path ToAbsolutePath(base::Path const &path)
	{
		if (path.IsAbsolutePath())
		{
			return path;
		}

		base::Path current_path = CurrentPath();
		base::Path ret = current_path + path;
		return ret;
	}

	///
	/// @brief 检查指定路径是否存在。
	///
	/// @param path
	///
	/// @return 不管它是目录还是文件，只要存在就返回 true.
	///
	bool Exists(base::Path const &path);

	///
	/// @brief 读取符号链接指向的路径。
	///
	/// @param symbolic_link_obj_path
	///
	/// @return
	///
	base::Path ReadSymboliclink(base::Path const &symbolic_link_obj_path);

	///
	/// @brief 创建符号链接。
	///
	/// @param symbolic_link_obj_path 符号链接这个对象本身所在的路径。
	/// @param link_to_path 创建的符号链接指向的路径。
	///
	void CreateSymboliclink(base::Path const &symbolic_link_obj_path,
							base::Path const &link_to_path);

	///
	/// @brief 创建符号链接。
	///
	/// @param symbolic_link_obj_path 符号链接这个对象本身所在的路径。
	///
	/// @param link_to_path 创建的符号链接指向的路径。
	///
	/// @param is_directory 为 true 表示要创建的符号链接指向一个目录，
	/// 为 false 表示要创建的符号链接指向一个文件。
	///
	/// 	@note windows 的傻逼设计，符号链接自己储存了一个信息来表示链接目标是不是目录。
	/// 	创建符号链接时就必须向函数传入这个信息。
	///
	void CreateSymboliclink(base::Path const &symbolic_link_obj_path,
							base::Path const &link_to_path,
							bool is_directory);

	///
	/// @brief 创建一个目录。
	///
	/// @param path 要创建的目录的路径。
	/// @note 不支持通过多层路径直接创建深层目录。
	///
	void CreateDirectory(base::Path const &path);

	///
	/// @brief 递归地创建一个目录。
	///
	/// @param path 要创建的目录的路径。
	///
	void CreateDirectoryRecursively(base::Path const &path);

	///
	/// @brief 确保目标路径是一个存在的目录。如果目标路径不存在，会创建空目录。
	///
	/// @note 支持递归创建目录。
	///
	/// @param path 要确保存在的目录路径。
	///
	inline void EnsureDirectory(base::Path const &path)
	{
		if (!base::filesystem::Exists(path))
		{
			// 目标路径不存在，则创建空目录
			base::filesystem::CreateDirectoryRecursively(path);
			return;
		}

		// 目标路径存在
		if (!base::filesystem::IsDirectory(path))
		{
			std::string message = CODE_POS_STR;

			message += std::format("目标路径 {} 已存在但不是目录。",
								   path.ToString());

			throw std::runtime_error{message};
		}
	}

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
	/// @note 其中的符号链接本身会被复制，不会进入到符号链接指向的实际位置去复制文件。
	///
	/// @param source_path 源路径。
	///
	/// @param destination_path 目标路径
	/// 	@note source_path 指向的对象复制后将是这个路径。也就是复制可以顺便重命名。
	///
	/// @param overwrite_method
	///
	void Copy(base::Path const &source_path,
			  base::Path const &destination_path,
			  base::filesystem::OverwriteOption overwrite_method);

	///
	/// @brief 将文件或目录从 source_path 移动到 destination_path.
	///
	/// @param source_path
	///
	/// @param destination_path 目标路径。
	/// 	@note source_path 指向的对象移动后将是这个路径。也就是移动可以顺便重命名。
	///
	/// @param overwrite_method
	///
	void Move(base::Path const &source_path,
			  base::Path const &destination_path,
			  base::filesystem::OverwriteOption overwrite_method);

	///
	/// @brief 目录条目。
	///
	/// @note 只要是能放在目录中的条目都是目录条目。例如：目录、符号链接、普通文件、设备文件等。
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
		DirectoryEntry(base::Path const &path)
			: _path(path)
		{
		}

		base::Path const &Path() const
		{
			return _path;
		}

		///
		/// @brief 本条目在文件系统中是否真实存在。
		///
		/// @return
		///
		bool Exists() const
		{
			return base::filesystem::Exists(_path);
		}

		/* #region 访问权限 */

		///
		/// @brief 本条目是否可读。
		///
		/// @return
		///
		bool IsReadable() const
		{
			return base::filesystem::IsReadable(_path);
		}

		///
		/// @brief 本条目是否可写。
		///
		/// @return
		///
		bool IsWriteable() const
		{
			return base::filesystem::IsWriteable(_path);
		}

		///
		/// @brief 本条目是否可执行。
		///
		/// @return
		///
		bool IsExcuteable() const
		{
			return base::filesystem::IsExcuteable(_path);
		}

		/* #endregion */

		/* #region 类型判断 */

		///
		/// @brief 检查本条目是否是目录。
		///
		/// @return
		///
		bool IsDirectory() const
		{
			return base::filesystem::IsDirectory(_path);
		}

		///
		/// @brief 是常规文件。
		///
		/// @note 常规文件是文件系统中储存在磁盘等介质中的数据，不是设备文件或套接字之类的抽象出来
		/// 映射到文件系统中的文件。
		///
		/// @return
		///
		bool IsRegularFile() const
		{
			return base::filesystem::IsRegularFile(_path);
		}

		///
		/// @brief 是符号链接。
		///
		/// @return
		///
		bool IsSymbolicLink() const
		{
			return base::filesystem::IsSymbolicLink(_path);
		}

		/* #endregion */
	};

	/* #region 迭代目录条目 */

	/* #region 接口函数 */

	///
	/// @brief 创建目录条目迭代器。
	///
	/// @param path
	/// @return
	///
	std::shared_ptr<base::IEnumerator<base::filesystem::DirectoryEntry const>> CreateDirectoryEntryEnumerator(base::Path const &path);

	///
	/// @brief 创建目录条目递归迭代器。
	///
	/// @param path
	/// @return
	///
	std::shared_ptr<base::IEnumerator<base::filesystem::DirectoryEntry const>> CreateDirectoryEntryRecursiveEnumerator(base::Path const &path);

	/* #endregion */

	///
	/// @brief 包装目录条目迭代器。
	///
	///
	class DirectoryEntryEnumerable :
		public base::IEnumerable<base::filesystem::DirectoryEntry const>
	{
	private:
		std::shared_ptr<base::IEnumerator<base::filesystem::DirectoryEntry const>> _it;

	public:
		DirectoryEntryEnumerable(base::Path const &path)
		{
			_it = CreateDirectoryEntryEnumerator(path);
		}

		///
		/// @brief 获取非 const 迭代器
		///
		/// @return
		///
		virtual std::shared_ptr<base::IEnumerator<base::filesystem::DirectoryEntry const>> GetEnumerator() override
		{
			return _it;
		}
	};

	///
	/// @brief 包装目录条目递归迭代器。
	///
	class RecursiveDirectoryEntryEnumerable :
		public base::IEnumerable<base::filesystem::DirectoryEntry const>
	{
	private:
		std::shared_ptr<base::IEnumerator<base::filesystem::DirectoryEntry const>> _it;

	public:
		RecursiveDirectoryEntryEnumerable(base::Path const &path)
		{
			_it = CreateDirectoryEntryRecursiveEnumerator(path);
		}

		///
		/// @brief 获取非 const 迭代器
		///
		/// @return
		///
		virtual std::shared_ptr<base::IEnumerator<base::filesystem::DirectoryEntry const>> GetEnumerator() override
		{
			return _it;
		}
	};

	/* #endregion */

} // namespace base::filesystem
