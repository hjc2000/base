#pragma once
#include "base/Console.h"
#include "base/embedded/flash/Flash.h"
#include "base/embedded/flash/LittleFsFlash.h"
#include "base/string/define.h"
#include <string>

namespace base
{
	namespace test
	{
		inline void TestLittleFsFlash()
		{
			base::flash::Flash flash{1};
			flash.Initialize();
			base::flash::LittleFsFlash little_fs_flash{flash};
			little_fs_flash.Mount();

			lfs_file_t file{};
			little_fs_flash.OpenOrCreateFile(file, "test_file");

			base::console().WriteLine("文件指针：" + std::to_string(little_fs_flash.GetFilePosition(file)));

			base::console().WriteLine(CODE_POS_STR + "测试成功。");
		}

	} // namespace test
} // namespace base
