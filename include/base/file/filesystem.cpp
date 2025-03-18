#include "filesystem.h"

#if HAS_THREAD
	#include <unistd.h>

/* #region 访问权限检查 */

bool base::filesystem::is_readable(std::string const &path)
{
	return access(path.c_str(), R_OK);
}

bool base::filesystem::is_writeable(std::string const &path)
{
	return access(path.c_str(), W_OK);
}

bool base::filesystem::is_excuteable(std::string const &path)
{
	return access(path.c_str(), X_OK);
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

#endif
