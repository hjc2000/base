#pragma once
#include "base/filesystem/file.h"
#include "base/filesystem/filesystem.h"
#include "base/filesystem/Path.h"
#include "base/stream/Span.h"
#include "base/string/String.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace base
{
	///
	/// @brief 修复单个 “哔哩哔哩 UWP 版” 下载的被故意损坏，从而不让用户用
	/// 自己的其他播放器播放的视频。
	///
	/// @param video_path 待修复的视频文件路径。
	///
	inline void fix_bilibili_uwp_mp4_video(base::Path const &video_path)
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

		source_video->CopyTo(out_video,
							 static_cast<int64_t>(16) * 1024 * 1024,
							 nullptr);

		std::cout << "修复完成" << std::endl;
	}

	///
	/// @brief 批量修复所有 “哔哩哔哩 UWP 版” 下载的被故意损坏，从而不让用户用
	/// 自己的其他播放器播放的视频。
	///
	/// @param video_dir 储存着 “哔哩哔哩 UWP 版” 下载的视频的目录。
	/// 	@note 会递归遍历其中的所有 mp4 文件进行修复。
	///
	inline void fix_all_bilibili_uwp_video(base::Path const &video_dir)
	{
		std::vector<base::Path> mp4_video_paths{};

		// 先收集所有待修复的视频文件的路径。
		//
		// 这么做是因为等会修复的时候会产生新文件，会改变目录内容，可能会影响到
		// 文件迭代过程。
		for (base::DirectoryEntry const &entry : base::filesystem::RecursiveDirectoryEntryEnumerable{video_dir})
		{
			if (base::String{entry.Path().LastName().ToString()}.StartWith("fixed_"))
			{
				continue;
			}

			if (entry.Path().ExtensionName() == "mp4")
			{
				mp4_video_paths.push_back(entry.Path());
			}
		}

		for (base::Path const &path : mp4_video_paths)
		{
			fix_bilibili_uwp_mp4_video(path);
			std::cout << std::endl;
		}
	}

} // namespace base
