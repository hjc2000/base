#include "filesystem.h"
#include "base/string/define.h"
#include <filesystem>

#if HAS_THREAD
	#include <unistd.h>

/* #region 访问权限检查 */

bool base::filesystem::is_readable(std::string const &path)
{
	return access(path.c_str(), R_OK) == 0;
}

bool base::filesystem::is_writeable(std::string const &path)
{
	return access(path.c_str(), W_OK) == 0;
}

bool base::filesystem::is_excuteable(std::string const &path)
{
	return access(path.c_str(), X_OK) == 0;
}

/* #endregion */

/* #region 目标类型检查 */

bool base::filesystem::is_directory(std::string const &path)
{
	std::error_code error_code{};
	bool ret = std::filesystem::is_directory(path, error_code);
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

bool base::filesystem::is_regular_file(std::string const &path)
{
	std::error_code error_code{};
	bool ret = std::filesystem::is_regular_file(path, error_code);
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

bool base::filesystem::is_symbolic_link(std::string const &path)
{
	std::error_code error_code{};
	bool ret = std::filesystem::is_symlink(path, error_code);
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

bool base::filesystem::exists(std::string const &path)
{
	std::error_code error_code{};
	bool ret = std::filesystem::exists(path, error_code);
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

std::string base::filesystem::read_symlink(std::string const &path)
{
	if (!is_symbolic_link(path))
	{
		throw std::runtime_error{CODE_POS_STR + "传进来的路径必须是一个符号链接的路径。"};
	}

	std::error_code error_code{};
	std::filesystem::path target_path = std::filesystem::read_symlink(path, error_code);
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

void base::filesystem::create_directory(std::string const &path)
{
	if (base::filesystem::exists(path))
	{
		std::string message = CODE_POS_STR;
		message += std::format("目标路径 {} 已存在。", path);
		throw std::runtime_error{message};
	}

	std::error_code error_code{};
	bool ret = std::filesystem::create_directory(path, error_code);
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

void base::filesystem::remove(std::string const &path)
{
	if (!exists(path))
	{
		// 路径不存在，直接返回。
		return;
	}

	std::error_code error_code{};

	// 返回值是 uintmax_t ，含义是递归删除的项目总数。
	auto removed_count = std::filesystem::remove_all(path, error_code);
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

void base::filesystem::copy(std::string const &source_path,
							std::string const &destination_path)
{
	if (!base::filesystem::exists(source_path))
	{
		std::string message = CODE_POS_STR;
		message += std::format("源路径 {} 不存在。", source_path);
		throw std::runtime_error{message};
	}

	if (base::filesystem::exists(destination_path))
	{
		std::string message = CODE_POS_STR;
		message += std::format("目标路径 {} 已存在。", destination_path);
		throw std::runtime_error{message};
	}

	std::error_code error_code{};

	std::filesystem::copy_options options = std::filesystem::copy_options::recursive |
											std::filesystem::copy_options::overwrite_existing |
											std::filesystem::copy_options::copy_symlinks;

	std::filesystem::copy(source_path,
						  destination_path,
						  options,
						  error_code);

	if (error_code.value() != 0)
	{
		std::string message = CODE_POS_STR;

		message += std::format("拷贝失败。错误代码：{}，错误消息：{}",
							   error_code.value(),
							   error_code.message());

		throw std::runtime_error{message};
	}
}

void base::filesystem::move(std::string const &source_path,
							std::string const &destination_path)
{
	if (!base::filesystem::exists(source_path))
	{
		std::string message = CODE_POS_STR;
		message += std::format("源路径 {} 不存在。", source_path);
		throw std::runtime_error{message};
	}

	if (base::filesystem::exists(destination_path))
	{
		std::string message = CODE_POS_STR;
		message += std::format("目标路径 {} 已存在。", destination_path);
		throw std::runtime_error{message};
	}

	std::error_code error_code{};

	std::filesystem::rename(source_path,
							destination_path,
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

void base::filesystem::copy_append_directory(std::string const &source_path,
											 std::string const &destination_path,
											 bool overwrite_existing_file)
{
	if (!base::filesystem::exists(source_path))
	{
		std::string message = CODE_POS_STR;
		message += std::format("源路径 {} 不存在。", source_path);
		throw std::runtime_error{message};
	}

	if (!base::filesystem::is_directory(source_path))
	{
		std::string message = CODE_POS_STR;
		message += std::format("源路径 {} 存在但不是一个目录，无法将源目录追加到目标目录。", source_path);
		throw std::runtime_error{message};
	}

	if (base::filesystem::exists(destination_path) &&
		!base::filesystem::is_directory(destination_path))
	{
		std::string message = CODE_POS_STR;
		message += std::format("目标路径 {} 存在且不是一个目录，无法将内容追加到目标路径。", source_path);
		throw std::runtime_error{message};
	}

	throw std::runtime_error{CODE_POS_STR + "还未完成"};
}

#endif
