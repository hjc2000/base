#pragma once
#include "base/container/List.h"
#include "base/filesystem/filesystem.h"
#include "base/filesystem/Path.h"
#include "base/string/String.h"
#include <cstdint>
#include <iostream>
#include <string>

namespace base::usage
{
	class RenameWithNumberingWorker
	{
	private:
		base::Path _work_path{};

		///
		/// @brief 收集工作区中的文件，返回文件路径列表。
		///
		/// @note 这里面的路径都会被转化为绝对路径。
		///
		/// @return
		///
		base::List<base::Path> CollectFiles()
		{
			base::List<base::Path> ret{};

			for (base::DirectoryEntry const &entry : base::filesystem::DirectoryEntryEnumerable{_work_path})
			{
				if (!entry.IsRegularFile())
				{
					continue;
				}

				base::Path file_path = entry.Path();

				if (file_path.ExtensionName() == "ini")
				{
					continue;
				}

				file_path = base::filesystem::ToAbsolutePath(file_path);
				ret.Add(file_path);
			}

			return ret;
		}

		///
		/// @brief 收集工作区中的文件，重命名加上前缀。
		///
		void AddPrefix()
		{
			base::List<base::Path> file_paths = CollectFiles();

			for (base::Path const &file_path : file_paths)
			{
				base::Path dir = file_path.ParentPath();
				base::Path old_name = file_path.LastName();
				base::Path new_name{"prefix_" + old_name.ToString()};
				base::Path new_file_path = dir + new_name;

				base::filesystem::Move(file_path,
									   new_file_path,
									   base::filesystem::OverwriteOption::Skip);
			}
		}

	public:
		///
		/// @brief
		///
		/// @param work_path 工作区路径。
		///
		RenameWithNumberingWorker(base::Path const &work_path)
		{
			_work_path = work_path;
		}

		///
		/// @brief 执行编号重命名。
		///
		/// @note 使用从 1 开始递增的编号给文件重命名。
		///
		void RenameWithNumbering()
		{
			AddPrefix();

			base::List<base::Path> file_paths = CollectFiles();

			// 进行自然排序。
			base::simple_natural_sort(file_paths);

			int64_t count = 1;

			for (base::Path const &file_path : file_paths)
			{
				// 获取文件所在的目录。
				base::Path file_dir = file_path.ParentPath();

				// 新的文件路径。等会儿会将文件移动为这个路径，从而进行重命名。
				base::Path new_file_path;

				// 循环，直到找到一个还没被使用的数字文件名。
				while (true)
				{
					base::String new_file_name = std::to_string(count++) + "." + file_path.ExtensionName();
					new_file_path = file_dir + new_file_name;

					if (!base::filesystem::Exists(new_file_path))
					{
						break;
					}
				}

				std::cout << "将 " << file_path << " 重命名为 " << new_file_path << std::endl;

				base::filesystem::Move(file_path,
									   new_file_path,
									   base::filesystem::OverwriteOption::Skip);
			}
		}
	};

} // namespace base::usage
