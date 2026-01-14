#pragma once
#include "base/filesystem/filesystem.h"
#include "base/filesystem/Path.h"
#include "base/string/Parse.h"
#include "base/string/String.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace base::usage
{
	inline void rename_with_numbering()
	{
		std::vector<base::Path> files{};

		for (base::DirectoryEntry const &entry : base::filesystem::DirectoryEntryEnumerable{""})
		{
			if (!entry.IsRegularFile())
			{
				continue;
			}

			base::Path file_path = entry.Path();
			base::Path name_without_extension = file_path.NameWithoutExtension();

			try
			{
				base::Parse<int64_t>(name_without_extension.ToString(), 10);
				std::cout << "跳过：" << name_without_extension << std::endl;
				continue;
			}
			catch (...)
			{
			}

			files.push_back(file_path);
		}

		int64_t count = 1;

		for (base::Path const &file : files)
		{
			base::Path dir = file;
			dir = base::filesystem::ToAbsolutePath(dir);
			dir = dir.ParentPath();

			base::Path new_file_path;

			while (true)
			{
				base::String new_file_name = std::to_string(count++) + "." + file.ExtensionName();
				new_file_path = dir + new_file_name;

				if (!base::filesystem::Exists(new_file_path))
				{
					break;
				}
			}

			std::cout << "将 " << file << " 重命名为 " << new_file_path << std::endl;

			base::filesystem::Move(file,
								   new_file_path,
								   base::filesystem::OverwriteOption::Skip);
		}
	}

} // namespace base::usage
