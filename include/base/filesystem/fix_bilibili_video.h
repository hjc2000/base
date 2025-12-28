#pragma once
#include "base/filesystem/file.h"
#include "base/filesystem/Path.h"
#include "base/stream/Span.h"
#include "file.h"
#include <cstdint>
#include <iostream>
#include <string>

namespace base
{
	inline void fix_bilibili_uwp_video(base::Path const &video_path)
	{
		std::shared_ptr<base::Stream> source_video = base::file::OpenReadOnly(video_path);

		base::Path out_dir = video_path.ParentPath();
		std::string out_video_name = "fixed_" + video_path.LastName().ToString();
		base::Path out_video_path = out_dir + out_video_name;
		std::cout << "输出文件：" << out_video_path << std::endl;
		std::shared_ptr<base::Stream> out_video = base::file::CreateNewAnyway(out_video_path);

		// 视频开头有 3 个 0xff 垃圾数据，需要丢弃。
		uint8_t first_three_bytes[3];
		source_video->Read(base::Span{first_three_bytes, sizeof(first_three_bytes)});

		bool first_three_bytes_are_all_ff = true;

		for (uint64_t i = 0; i < sizeof(first_three_bytes); i++)
		{
			if (first_three_bytes[i] != 0xff)
			{
				first_three_bytes_are_all_ff = false;
				break;
			}
		}

		if (!first_three_bytes_are_all_ff)
		{
			base::ReadOnlySpan first_three_bytes_span{
				first_three_bytes,
				sizeof(first_three_bytes),
			};

			out_video->Write(first_three_bytes_span);
			std::cout << "不需要修复" << std::endl;
		}

		source_video->CopyTo(out_video, nullptr);
	}

} // namespace base
