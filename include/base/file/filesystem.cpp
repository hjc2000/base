#include "filesystem.h"

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
	return std::filesystem::is_directory(path);
}

bool base::filesystem::is_regular_file(std::string const &path)
{
	return std::filesystem::is_regular_file(path);
}

bool base::filesystem::is_symbolic_link(std::string const &path)
{
	return std::filesystem::is_symlink(path);
}

/* #endregion */

bool base::filesystem::exists(std::string const &path)
{
	return std::filesystem::exists(path);
}

std::string base::filesystem::read_symlink(std::string const &path)
{
	if (!is_symbolic_link(path))
	{
		throw std::runtime_error{CODE_POS_STR + "传进来的路径必须是一个符号链接的路径。"};
	}

	std::filesystem::path target_path = std::filesystem::read_symlink(path);
	return target_path.string();
}

void base::filesystem::create_directory(std::string const &path)
{
	std::filesystem::create_directory(path);
}

void base::filesystem::remove(std::string const &path)
{
	if (!exists(path))
	{
		// 路径不存在，直接返回。
		return;
	}

	// 返回值是 uintmax_t ，含义是递归删除的项目总数。
	auto removed_count = std::filesystem::remove_all(path);
	if (removed_count == 0)
	{
		throw std::runtime_error{CODE_POS_STR + "删除失败。"};
	}
}

#endif
