#include "tool.h"
#include "base/filesystem/filesystem.h"
#include "base/filesystem/Path.h"
#include <cstdint>

#if HAS_THREAD

void base::filesystem::tool::batch_rename_files_to_numbers(base::Path const &input_path,
														   base::Path const &temp_path)
{
	uint64_t count = 0;
	for (base::filesystem::DirectoryEntry const &entry : base::filesystem::RecursiveDirectoryEntryEnumerable{input_path})
	{
		base::Path dst_path = entry.Path();
		dst_path.RemoveBasePath(input_path);
		dst_path.SetLastName(std::to_string(count++) + '.' + dst_path.ExtensionName());
		dst_path = temp_path + dst_path;
		std::cout << dst_path << std::endl;

		base::filesystem::Move(entry.Path(),
							   dst_path,
							   base::filesystem::OverwriteOption::Skip);
	}

	// 将输出目录移动到输入目录，覆盖输入目录
	base::filesystem::Move(temp_path,
						   input_path,
						   base::filesystem::OverwriteOption::Overwrite);

	std::cout << std::format("本次处理了: {} 个文件。", count) << std::endl;
}

#endif // HAS_THREAD
