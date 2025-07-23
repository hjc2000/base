#include "filesystem.h"
#include "base/container/iterator/IEnumerator.h"
#include "base/file/Path.h"
#include "base/string/define.h"
#include "DirectoryEntry.h"
#include <filesystem>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <system_error>
#include <unistd.h>

#if HAS_THREAD

namespace
{
	///
	/// @brief 拷贝单个文件。
	///
	/// @warning 这里没有进行检查。必须确保源路径是一个文件。
	///
	/// @param source_path
	///
	/// @param destination_path 目标路径
	/// 	@note 复制后的文件将是这个路径。也就是复制可以顺便重命名。
	///
	/// @param overwrite_method
	///
	void CopyFile(base::Path const &source_path,
				  base::Path const &destination_path,
				  base::filesystem::OverwriteOption overwrite_method)
	{
		std::filesystem::copy_options options = std::filesystem::copy_options::copy_symlinks;

		if (!base::filesystem::Exists(destination_path))
		{
			// 目标路径不存在，直接复制。
			base::filesystem::EnsureDirectory(destination_path.ParentPath());
			std::cout << "复制：" << source_path << " --> " << destination_path << std::endl;
			std::filesystem::copy(source_path.ToString(), destination_path.ToString(), options);
			return;
		}

		// 目标路径存在
		if (overwrite_method == base::filesystem::OverwriteOption::Skip)
		{
			std::cout << "跳过：" << source_path << " --> " << destination_path << std::endl;
			return;
		}

		if (overwrite_method == base::filesystem::OverwriteOption::Overwrite)
		{
			// 无条件覆盖。
			base::filesystem::Remove(destination_path);
			std::filesystem::copy(source_path.ToString(), destination_path.ToString(), options);
			std::cout << "覆盖：" << source_path << " --> " << destination_path << std::endl;
			return;
		}

		// 如果更新则覆盖
		std::filesystem::directory_entry src_entry{source_path.ToString()};
		std::filesystem::directory_entry dst_entry{destination_path.ToString()};
		if (src_entry.last_write_time() <= dst_entry.last_write_time())
		{
			std::cout << "不更新：" << source_path << " --> " << destination_path << std::endl;
			return;
		}

		// 需要更新
		base::filesystem::Remove(destination_path);
		std::filesystem::copy(source_path.ToString(), destination_path.ToString(), options);
		std::cout << "更新：" << source_path << " --> " << destination_path << std::endl;
		return;
	}

	/* #region 目录条目迭代器 */

	///
	/// @brief 目录条目迭代器。
	///
	///
	class DirectoryEntryEnumerator :
		public base::IEnumerator<base::DirectoryEntry const>
	{
	private:
		base::DirectoryEntry _current;
		std::filesystem::directory_iterator _current_it;
		std::filesystem::directory_iterator _end_it;

	public:
		DirectoryEntryEnumerator(base::Path const &path)
		{
			std::string path_str = path.ToString();
			if (path_str == "")
			{
				path_str = "./";
			}

			_current_it = std::filesystem::directory_iterator{path_str};
		}

		///
		/// @brief 迭代器当前是否指向尾后元素。
		///
		/// @return
		///
		virtual bool IsEnd() const override
		{
			return _current_it == _end_it;
		}

		///
		/// @brief 获取当前值的引用。
		///
		/// @return ItemType&
		///
		virtual base::DirectoryEntry const &CurrentValue() override
		{
			_current = base::DirectoryEntry{_current_it->path().string()};
			return _current;
		}

		///
		/// @brief 递增迭代器的位置。
		///
		///
		virtual void Add() override
		{
			++_current_it;
		}
	};

	///
	/// @brief 目录条目递归迭代器。
	///
	///
	class RecursiveDirectoryEntryEnumerator :
		public base::IEnumerator<base::DirectoryEntry const>
	{
	private:
		base::DirectoryEntry _current;
		std::filesystem::recursive_directory_iterator _current_it;
		std::filesystem::recursive_directory_iterator _end_it;

	public:
		RecursiveDirectoryEntryEnumerator(base::Path const &path)
		{
			std::string path_str = path.ToString();
			if (path_str == "")
			{
				path_str = "./";
			}

			_current_it = std::filesystem::recursive_directory_iterator{path_str};
		}

		///
		/// @brief 迭代器当前是否指向尾后元素。
		///
		/// @return
		///
		virtual bool IsEnd() const override
		{
			return _current_it == _end_it;
		}

		///
		/// @brief 获取当前值的引用。
		///
		/// @return ItemType&
		///
		virtual base::DirectoryEntry const &CurrentValue() override
		{
			_current = base::DirectoryEntry{_current_it->path().string()};
			return _current;
		}

		///
		/// @brief 递增迭代器的位置。
		///
		///
		virtual void Add() override
		{
			++_current_it;
		}
	};

	/* #endregion */

} // namespace

/* #region 访问权限检查 */

bool base::filesystem::IsReadable(base::Path const &path)
{
	return access(path.ToString().c_str(), R_OK) == 0;
}

bool base::filesystem::IsWriteable(base::Path const &path)
{
	return access(path.ToString().c_str(), W_OK) == 0;
}

bool base::filesystem::IsExcuteable(base::Path const &path)
{
	return access(path.ToString().c_str(), X_OK) == 0;
}

/* #endregion */

/* #region 目标类型检查 */

bool base::filesystem::IsDirectory(base::Path const &path)
{
	std::error_code error_code{};
	bool ret = std::filesystem::is_directory(path.ToString(), error_code);
	if (error_code.value() != 0)
	{
		std::string message = CODE_POS_STR;

		message += std::format("错误代码：{}，错误消息：{}",
							   error_code.value(),
							   error_code.message());

		throw std::runtime_error{message};
	}

	return ret;
}

bool base::filesystem::IsRegularFile(base::Path const &path)
{
	std::error_code error_code{};
	bool ret = std::filesystem::is_regular_file(path.ToString(), error_code);
	if (error_code.value() != 0)
	{
		std::string message = CODE_POS_STR;

		message += std::format("错误代码：{}，错误消息：{}",
							   error_code.value(),
							   error_code.message());

		throw std::runtime_error{message};
	}

	return ret;
}

bool base::filesystem::IsSymbolicLink(base::Path const &path)
{
	std::error_code error_code{};
	bool ret = std::filesystem::is_symlink(path.ToString(), error_code);
	if (error_code.value() != 0)
	{
		std::string message = CODE_POS_STR;

		message += std::format("错误代码：{}，错误消息：{}",
							   error_code.value(),
							   error_code.message());

		throw std::runtime_error{message};
	}

	return ret;
}

/* #endregion */

bool base::filesystem::Exists(base::Path const &path)
{
	std::error_code error_code{};
	bool ret = std::filesystem::exists(path.ToString(), error_code);
	if (error_code.value() != 0)
	{
		std::string message = CODE_POS_STR;

		message += std::format("检查文件是否存在失败。错误代码：{}，错误消息：{}",
							   error_code.value(),
							   error_code.message());

		throw std::runtime_error{message};
	}

	return ret;
}

base::Path base::filesystem::ReadSymlink(base::Path const &path)
{
	if (!base::filesystem::IsSymbolicLink(path))
	{
		throw std::runtime_error{CODE_POS_STR + "传进来的路径必须是一个符号链接的路径。"};
	}

	std::error_code error_code{};
	std::filesystem::path target_path = std::filesystem::read_symlink(path.ToString(), error_code);
	if (error_code.value() != 0)
	{
		std::string message = CODE_POS_STR;

		message += std::format("读取符号链接失败。错误代码：{}，错误消息：{}",
							   error_code.value(),
							   error_code.message());

		throw std::runtime_error{message};
	}

	return target_path.string();
}

/* #region 创建目录 */

void base::filesystem::CreateDirectory(base::Path const &path)
{
	if (base::filesystem::Exists(path))
	{
		std::string message = CODE_POS_STR;
		message += std::format("目标路径 {} 已存在。", path.ToString());
		throw std::runtime_error{message};
	}

	std::error_code error_code{};
	bool ret = std::filesystem::create_directory(path.ToString(), error_code);
	if (error_code.value() != 0)
	{
		std::string message = CODE_POS_STR;

		message += std::format("创建目录失败。错误代码：{}，错误消息：{}",
							   error_code.value(),
							   error_code.message());

		throw std::runtime_error{message};
	}

	if (!ret)
	{
		std::string message = CODE_POS_STR + "创建目录失败，但是没有错误代码。";
		throw std::runtime_error{message};
	}
}

void base::filesystem::CreateDirectoryRecursively(base::Path const &path)
{
	if (base::filesystem::Exists(path))
	{
		std::string message = CODE_POS_STR;
		message += std::format("目标路径 {} 已存在。", path.ToString());
		throw std::runtime_error{message};
	}

	std::error_code error_code{};
	bool ret = std::filesystem::create_directories(path.ToString(), error_code);
	if (error_code.value() != 0)
	{
		std::string message = CODE_POS_STR;

		message += std::format("创建目录失败。错误代码：{}，错误消息：{}",
							   error_code.value(),
							   error_code.message());

		throw std::runtime_error{message};
	}

	if (!ret)
	{
		std::string message = CODE_POS_STR + "创建目录失败，但是没有错误代码。";
		throw std::runtime_error{message};
	}
}

/* #endregion */

void base::filesystem::Remove(base::Path const &path)
{
	if (!Exists(path))
	{
		// 路径不存在，直接返回。
		return;
	}

	std::error_code error_code{};

	// 返回值是 uintmax_t ，含义是递归删除的项目总数。
	auto removed_count = std::filesystem::remove_all(path.ToString(), error_code);
	if (error_code.value() != 0)
	{
		std::string message = std::format("{} 删除失败。错误代码：{}，错误消息：{}",
										  CODE_POS_STR,
										  error_code.value(),
										  error_code.message());

		throw std::runtime_error{message};
	}

	if (removed_count == 0)
	{
		std::string message = CODE_POS_STR + "删除失败，因为删除了 0 个项目，但是没有错误代码。";
		throw std::runtime_error{message};
	}
}

void base::filesystem::Copy(base::Path const &source_path,
							base::Path const &destination_path,
							base::filesystem::OverwriteOption overwrite_method)
{
	if (!base::filesystem::Exists(source_path))
	{
		std::string message = CODE_POS_STR;
		message += std::format("源路径 {} 不存在。", source_path.ToString());
		throw std::runtime_error{message};
	}

	// 执行到这里说明源路径存在
	if (IsFile(source_path))
	{
		CopyFile(source_path, destination_path, overwrite_method);
		return;
	}

	// 执行到这里说明源路径是目录
	EnsureDirectory(destination_path);

	// 开始递归复制
	for (auto entry : std::filesystem::recursive_directory_iterator(source_path.ToString()))
	{
		base::Path relative_path{entry.path().string()};
		relative_path.RemoveBasePath(source_path);

		base::Path src_path = source_path + relative_path;
		base::Path dst_path = destination_path + relative_path;

		if (IsFile(src_path))
		{
			// 源路径是一个文件
			CopyFile(src_path, dst_path, overwrite_method);
		}
		else
		{
			// 源路径是一个目录
			EnsureDirectory(dst_path);
		}
	}
}

void base::filesystem::Move(base::Path const &source_path,
							base::Path const &destination_path,
							base::filesystem::OverwriteOption overwrite_method)
{
	if (!base::filesystem::Exists(source_path))
	{
		std::string message = CODE_POS_STR;
		message += std::format("源路径 {} 不存在。", source_path.ToString());
		throw std::runtime_error{message};
	}

	if (!base::filesystem::Exists(destination_path))
	{
		// 目标路径不存在，直接移动

		// 先确保父目录存在，否则会抛出异常
		EnsureDirectory(destination_path.ParentPath());
		std::error_code error_code{};

		std::filesystem::rename(source_path.ToString(),
								destination_path.ToString(),
								error_code);

		if (error_code.value() != 0)
		{
			std::string message = CODE_POS_STR;

			message += std::format("移动失败。错误代码：{}，错误消息：{}",
								   error_code.value(),
								   error_code.message());

			throw std::runtime_error{message};
		}

		return;
	}

	// 目标路径存在
	if (overwrite_method == base::filesystem::OverwriteOption::Skip)
	{
		return;
	}

	if (overwrite_method == base::filesystem::OverwriteOption::Overwrite)
	{
		// 直接覆盖目标文件
		Remove(destination_path);
		std::error_code error_code{};

		std::filesystem::rename(source_path.ToString(),
								destination_path.ToString(),
								error_code);

		if (error_code.value() != 0)
		{
			std::string message = CODE_POS_STR;

			message += std::format("移动失败。错误代码：{}，错误消息：{}",
								   error_code.value(),
								   error_code.message());

			throw std::runtime_error{message};
		}

		return;
	}

	// 如果更新则覆盖
	std::filesystem::directory_entry src_entry{source_path.ToString()};
	std::filesystem::directory_entry dst_entry{destination_path.ToString()};
	if (src_entry.last_write_time() <= dst_entry.last_write_time())
	{
		std::cout << "不更新：" << source_path << " --> " << destination_path << std::endl;
		return;
	}

	// 需要更新
	Remove(destination_path);
	std::error_code error_code{};

	std::filesystem::rename(source_path.ToString(),
							destination_path.ToString(),
							error_code);

	if (error_code.value() != 0)
	{
		std::string message = CODE_POS_STR;

		message += std::format("移动失败。错误代码：{}，错误消息：{}",
							   error_code.value(),
							   error_code.message());

		throw std::runtime_error{message};
	}

	std::cout << "更新：" << source_path << " --> " << destination_path << std::endl;
	return;
}

std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> base::filesystem::CreateDirectoryEntryEnumerator(base::Path const &path)
{
	return std::shared_ptr<DirectoryEntryEnumerator>{new DirectoryEntryEnumerator{path}};
}

std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> base::filesystem::CreateDirectoryEntryRecursiveEnumerator(base::Path const &path)
{
	return std::shared_ptr<RecursiveDirectoryEntryEnumerator>{new RecursiveDirectoryEntryEnumerator{path}};
}

void base::test::TestDirectoryEntryEnumerable()
{
	base::filesystem::DirectoryEntryEnumerable entries{"C:/Users/huang/dev/.temp"};
	for (base::DirectoryEntry const &entry : entries)
	{
		std::cout << entry.Path() << std::endl;
	}
}

void base::test::TestRecursiveDirectoryEntryEnumerable()
{
	base::filesystem::RecursiveDirectoryEntryEnumerable entries{"C:/Users/huang/dev/.temp"};
	for (base::DirectoryEntry const &entry : entries)
	{
		std::cout << entry.Path() << std::endl;
	}
}

#endif // HAS_THREAD

/* #region EnsureDirectory */

void base::filesystem::EnsureDirectory(base::Path const &path)
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

/* #endregion */
