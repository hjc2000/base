#include "filesystem.h"
#include "base/file/Path.h"
#include "base/string/define.h"
#include <filesystem>
#include <string>
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
	void copy_file(base::Path const &source_path,
				   base::Path const &destination_path,
				   base::filesystem::OverwriteOption overwrite_method)
	{
		std::filesystem::copy_options options = std::filesystem::copy_options::copy_symlinks;

		if (!base::filesystem::exists(destination_path))
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

		if (base::filesystem::is_directory(destination_path))
		{
			std::string message = CODE_POS_STR;
			message += std::format("目标路径 {} 存在且是一个目录，并且覆写选项不是指定 Skip。", source_path.ToString());
			throw std::runtime_error{message};
		}

		if (overwrite_method == base::filesystem::OverwriteOption::Overwrite)
		{
			// 无条件覆盖。
			base::filesystem::remove(destination_path);
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
		base::filesystem::remove(destination_path);
		std::filesystem::copy(source_path.ToString(), destination_path.ToString(), options);
		std::cout << "更新：" << source_path << " --> " << destination_path << std::endl;
		return;
	}
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

bool base::filesystem::is_directory(base::Path const &path)
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

bool base::filesystem::is_regular_file(base::Path const &path)
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

bool base::filesystem::is_symbolic_link(base::Path const &path)
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

bool base::filesystem::exists(base::Path const &path)
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

base::Path base::filesystem::read_symlink(base::Path const &path)
{
	if (!is_symbolic_link(path))
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

void base::filesystem::create_directory(base::Path const &path)
{
	if (base::filesystem::exists(path))
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

void base::filesystem::ensure_directory(base::Path const &path)
{
	if (!base::filesystem::exists(path))
	{
		// 目标路径不存在，则创建空目录
		base::filesystem::create_directory(path);
		return;
	}

	// 目标路径存在
	if (!base::filesystem::is_directory(path))
	{
		std::string message = CODE_POS_STR;

		message += std::format("目标路径 {} 已存在但不是目录。",
							   path.ToString());

		throw std::runtime_error{message};
	}
}

void base::filesystem::remove(base::Path const &path)
{
	if (!exists(path))
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

void base::filesystem::copy(base::Path const &source_path,
							base::Path const &destination_path,
							base::filesystem::OverwriteOption overwrite_method)
{
	if (!base::filesystem::exists(source_path))
	{
		std::string message = CODE_POS_STR;
		message += std::format("源路径 {} 不存在。", source_path.ToString());
		throw std::runtime_error{message};
	}

	// 执行到这里说明源路径存在
	if (is_file(source_path))
	{
		copy_file(source_path, destination_path, overwrite_method);
		return;
	}

	// 执行到这里说明源路径是目录
	ensure_directory(destination_path);

	// 开始递归复制
	for (auto entry : std::filesystem::recursive_directory_iterator(source_path.ToString()))
	{
		base::Path relative_path = base::Path{entry.path().string()}.RemoveBasePath(source_path);
		base::Path src_path = source_path + relative_path;
		base::Path dst_path = destination_path + relative_path;

		if (is_file(src_path))
		{
			// 源路径是一个文件
			copy_file(src_path, dst_path, overwrite_method);
		}
		else
		{
			// 源路径是一个目录
			ensure_directory(dst_path);
		}
	}
}

void base::filesystem::move(base::Path const &source_path,
							base::Path const &destination_path)
{
	if (!base::filesystem::exists(source_path))
	{
		std::string message = CODE_POS_STR;
		message += std::format("源路径 {} 不存在。", source_path.ToString());
		throw std::runtime_error{message};
	}

	if (base::filesystem::exists(destination_path))
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

#endif // HAS_THREAD
