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
		/// @param path 要创建的目录的路径。
		///
		/// @exception std::runtime_error 目标路径已存在会抛出异常。
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

		///
		/// @brief 将文件或目录从 source_path 复制到 destination_path.
		///
		/// @note 其中的符号链接本身会被赋值，不会进入到符号链接指向的实际位置去复制文件。
		///
		/// @param source_path
		/// @param destination_path
		///
		/// @exception std::runtime_error 目标路径已存在会抛出异常。
		///
		void copy(std::string const &source_path,
				  std::string const &destination_path);

		///
		/// @brief 将文件或目录从 source_path 移动到 destination_path.
		///
		/// @param source_path
		/// @param destination_path
		///
		/// @exception std::runtime_error 目标路径已存在会抛出异常。
		///
		void move(std::string const &source_path,
				  std::string const &destination_path);

		///
		/// @brief 将源路径的目录拷贝到目标路径的目录进行合并。
		///
		/// @param source_path 源路径，必须是一个目录。
		/// @param destination_path 目标路径。必须是不存在的路径或者已存在的目录。
		/// @param overwrite_existing_file 拷贝到目标路径时是否覆盖已存在的文件。
		///
		void copy_append_directory(std::string const &source_path,
								   std::string const &destination_path,
								   bool overwrite_existing_file);

	} // namespace filesystem
} // namespace base
