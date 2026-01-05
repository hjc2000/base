#pragma once
#include "Path.h"

namespace base
{
	namespace filesystem
	{
		namespace tool
		{
			///
			/// @brief 递归遍历指定路径下的文件，移动到输出目录并重命名为数字。
			///
			/// @param input_path 要被处理的文件所在的文件夹。
			/// @param temp_path 临时输出目录。
			///
			void batch_rename_files_to_numbers(base::Path const &input_path,
											   base::Path const &temp_path);

		} // namespace tool
	} // namespace filesystem
} // namespace base
