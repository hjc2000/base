#pragma once
#include <string>

namespace base
{
	namespace filesystem
	{
		/* #region 访问权限检查 */

		///
		/// @brief 检查文件或目录是否可读。
		///
		/// @param path
		/// @return true
		/// @return false
		///
		bool is_readable(std::string const &path);

		///
		/// @brief 检查文件或目录是否可写。
		///
		/// @param path
		/// @return true
		/// @return false
		///
		bool is_writeable(std::string const &path);

		///
		/// @brief 检查文件或目录是否可执行。
		///
		/// @note 对于目录，执行的意思是进入该目录。
		///
		/// @param path
		/// @return true
		/// @return false
		///
		bool is_excuteable(std::string const &path);
		/* #endregion */

		/* #region 目标类型检查 */

		///
		/// @brief 检查指定路径是否是一个目录。
		///
		/// @param path
		/// @return true
		/// @return false
		///
		bool is_directory(std::string const &path);

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
		bool is_regular_file(std::string const &path);

		///
		/// @brief 检查指定路径是否是一个符号链接。
		///
		/// @param path
		/// @return true
		/// @return false
		///
		bool is_symbolic_link(std::string const &path);
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
		bool exists(std::string const &path);

		///
		/// @brief 读取符号链接指向的路径。
		///
		/// @param path
		/// @return std::string
		///
		std::string read_symlink(std::string const &path);

		///
		/// @brief 创建一个目录。
		///
		/// @param path
		///
		void create_directory(std::string const &path);

		///
		/// @brief 删除目录或文件或符号链接。
		///
		/// @note 删除符号链接是是删除符号链接本身，不会跟踪到符号链接指向的位置去删除。
		///
		/// @param path
		///
		void remove(std::string const &path);

	} // namespace filesystem
} // namespace base
