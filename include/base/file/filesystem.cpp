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
	/// @param destination_path
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

		if (base::filesystem::IsDirectory(destination_path))
		{
			std::string message = CODE_POS_STR;
			message += std::format("目标路径 {} 存在且是一个目录，并且覆写选项不是指定 Skip。", source_path.ToString());
			throw std::runtime_error{message};
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

	///
	/// @brief 目录条目迭代器。
	///
	///
	class DirectoryEntryEnumerator :
		public base::IEnumerator<base::DirectoryEntry const>
	{
	private:
		std::string _path;
		base::DirectoryEntry _current;
		bool _move_to_next_for_the_first_time = true;
		std::filesystem::directory_iterator _begin;
		std::filesystem::directory_iterator _end;

	public:
		DirectoryEntryEnumerator(base::Path const &path)
		{
			_path = path.ToString();
			if (_path == "")
			{
				_path = "./";
			}

			Reset();
		}

		///
		/// @brief 获取当前值的引用。
		///
		/// @return ItemType&
		///
		virtual base::DirectoryEntry const &CurrentValue() override
		{
			if (_begin == _end)
			{
				std::string message = CODE_POS_STR +
									  "当前没有值，如果是刚刚构造或 Reset 要先调用 MoveNext. "
									  "也有可能是当前路径没有目录条目。"
									  "也有可能是已经遍历完了，要重新 Reset.";

				throw std::runtime_error{message};
			}

			_current = base::DirectoryEntry{_begin->path().string()};
			return _current;
		}

		///
		/// @brief 迭代器前进到下一个值。
		///
		/// @return true
		/// @return false
		///
		virtual bool MoveNext() override
		{
			if (_move_to_next_for_the_first_time)
			{
				_move_to_next_for_the_first_time = false;
			}
			else
			{
				++_begin;
			}

			return _begin != _end;
		}

		///
		/// @brief 将迭代器重置到容器开始的位置。
		///
		/// @note 开始位置是第一个元素前。也就是说重置后，要调用一次 MoveNext 才能获取到第一个值。
		///
		virtual void Reset() override
		{
			_move_to_next_for_the_first_time = true;
			_begin = std::filesystem::directory_iterator{_path};
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
		std::string _path;
		base::DirectoryEntry _current;
		bool _move_to_next_for_the_first_time = true;
		std::filesystem::recursive_directory_iterator _begin;
		std::filesystem::recursive_directory_iterator _end;

	public:
		RecursiveDirectoryEntryEnumerator(base::Path const &path)
		{
			_path = path.ToString();
			if (_path == "")
			{
				_path = "./";
			}

			Reset();
		}

		///
		/// @brief 获取当前值的引用。
		///
		/// @return ItemType&
		///
		virtual base::DirectoryEntry const &CurrentValue() override
		{
			if (_begin == _end)
			{
				std::string message = CODE_POS_STR +
									  "当前没有值，如果是刚刚构造或 Reset 要先调用 MoveNext. "
									  "也有可能是当前路径没有目录条目。"
									  "也有可能是已经遍历完了，要重新 Reset.";

				throw std::runtime_error{message};
			}

			_current = base::DirectoryEntry{_begin->path().string()};
			return _current;
		}

		///
		/// @brief 迭代器前进到下一个值。
		///
		/// @return true
		/// @return false
		///
		virtual bool MoveNext() override
		{
			if (_move_to_next_for_the_first_time)
			{
				_move_to_next_for_the_first_time = false;
			}
			else
			{
				++_begin;
			}

			return _begin != _end;
		}

		///
		/// @brief 将迭代器重置到容器开始的位置。
		///
		/// @note 开始位置是第一个元素前。也就是说重置后，要调用一次 MoveNext 才能获取到第一个值。
		///
		virtual void Reset() override
		{
			_move_to_next_for_the_first_time = true;
			_begin = std::filesystem::recursive_directory_iterator{_path};
		}
	};

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
	if (!IsSymbolicLink(path))
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

void base::filesystem::EnsureDirectory(base::Path const &path)
{
	if (!base::filesystem::Exists(path))
	{
		// 目标路径不存在，则创建空目录
		base::filesystem::CreateDirectory(path);
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
		std::string message = CODE_POS_STR +
							  std::format("删除失败。错误代码：{}，错误消息：{}",
										  error_code.value(),
										  error_code.message());

		throw std::runtime_error{message};
	}

	if (removed_count == 0)
	{
		std::string message = CODE_POS_STR + "删除失败，但是没有错误代码。";
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
		base::Path relative_path = base::Path{entry.path().string()}.RemoveBasePath(source_path);
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
							base::Path const &destination_path)
{
	if (!base::filesystem::Exists(source_path))
	{
		std::string message = CODE_POS_STR;
		message += std::format("源路径 {} 不存在。", source_path.ToString());
		throw std::runtime_error{message};
	}

	if (base::filesystem::Exists(destination_path))
	{
		std::string message = CODE_POS_STR;
		message += std::format("目标路径 {} 已存在。", destination_path.ToString());
		throw std::runtime_error{message};
	}

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
}

std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> base::filesystem::CreateDirectoryEntryEnumerator(base::Path const &path)
{
	return std::shared_ptr<DirectoryEntryEnumerator>{new DirectoryEntryEnumerator{path}};
}

std::shared_ptr<base::IEnumerator<base::DirectoryEntry const>> base::filesystem::CreateDirectoryEntryRecursiveEnumerator(base::Path const &path)
{
	return std::shared_ptr<RecursiveDirectoryEntryEnumerator>{new RecursiveDirectoryEntryEnumerator{path}};
}

#endif // HAS_THREAD

#if HAS_THREAD
void base::test::TestDirectoryEntryEnumerable()
{
	base::filesystem::DirectoryEntryEnumerable entries{"F:/.temp"};
	for (auto entry : entries)
	{
		std::cout << entry.Path() << std::endl;
	}
}

void base::test::TestRecursiveDirectoryEntryEnumerable()
{
	base::filesystem::RecursiveDirectoryEntryEnumerable entries{"F:/.temp"};
	for (auto entry : entries)
	{
		std::cout << entry.Path() << std::endl;
	}
}
#endif // HAS_THREAD
