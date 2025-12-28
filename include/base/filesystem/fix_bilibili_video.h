#pragma once
#include "base/filesystem/file.h"
#include "base/filesystem/filesystem.h"
#include "base/filesystem/Path.h"
#include "base/stream/Span.h"
#include "file.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace base
{
	inline void fix_bilibili_uwp_video(base::Path const &video_path)
	{
		std::cout << "尝试修复：" << video_path << std::endl;
		std::shared_ptr<base::Stream> source_video = base::file::OpenReadOnly(video_path);

		// 视频开头有 3 个 0xff 垃圾数据，需要丢弃。
		uint8_t leading_bytes[3];
		source_video->Read(base::Span{leading_bytes, sizeof(leading_bytes)});

		bool leading_bytes_are_all_ff = true;

		for (uint64_t i = 0; i < sizeof(leading_bytes); i++)
		{
			if (leading_bytes[i] != 0xff)
			{
				leading_bytes_are_all_ff = false;
				break;
			}
		}

		if (!leading_bytes_are_all_ff)
		{
			std::cout << "不需要修复" << std::endl;
			return;
		}

		base::Path out_dir = video_path.ParentPath();
		std::string out_video_name = "fixed_" + video_path.LastName().ToString();
		base::Path out_video_path = out_dir + out_video_name;
		std::cout << "输出文件：" << out_video_path << std::endl;
		std::shared_ptr<base::Stream> out_video = base::file::CreateNewAnyway(out_video_path);

		source_video->CopyTo(out_video, nullptr);
		std::cout << "修复完成" << std::endl;
	}

	inline void fix_all_bilibili_uwp_video(base::Path const &video_dir)
	{
		std::vector<base::Path> video_paths;

		for (base::DirectoryEntry const &entry : base::filesystem::RecursiveDirectoryEntryEnumerable{video_dir})
		{
			if (entry.Path().ExtensionName() == "mp4")
			{
				video_paths.push_back(entry.Path());
			}
		}

		for (base::Path const &path : video_paths)
		{
			fix_bilibili_uwp_video(path);
			std::cout << std::endl;
		}
	}

} // namespace base
