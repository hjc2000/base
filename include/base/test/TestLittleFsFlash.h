#pragma once
#include "base/Console.h"
#include "base/embedded/flash/Flash.h"
#include "base/embedded/flash/LittleFsFlash.h"
#include "base/stream/Span.h"
#include "base/string/define.h"
#include <cstdint>
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
			little_fs_flash.Remount();

			lfs_file_t file{};
			little_fs_flash.OpenOrCreateFile(file, "test_file");

			base::console().WriteLine("文件大小：" + std::to_string(little_fs_flash.GetFileSize(file)));
			little_fs_flash.SetFileSize(file, 6);
			base::console().WriteLine("文件大小：" + std::to_string(little_fs_flash.GetFileSize(file)));
			little_fs_flash.SetFileSize(file, 0);
			base::console().WriteLine("文件大小：" + std::to_string(little_fs_flash.GetFileSize(file)));

			base::console().WriteLine("文件指针：" + std::to_string(little_fs_flash.GetFilePosition(file)));

			uint32_t number = 666;
			base::Span num_span{reinterpret_cast<uint8_t *>(&number), sizeof(number)};
			little_fs_flash.WriteFile(file, num_span);
			little_fs_flash.ReadFile(file, num_span);
			base::console().WriteLine("读出数字：" + std::to_string(number));
			little_fs_flash.CloseFile(file);
			little_fs_flash.Unmount();

			base::console().WriteLine(CODE_POS_STR + "测试成功。");
		}

	} // namespace test
} // namespace base
