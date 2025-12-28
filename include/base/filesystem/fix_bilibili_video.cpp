#include "fix_bilibili_video.h" // IWYU pragma: keep
#include "base/filesystem/Path.h"
#include "base/stream/Span.h"
#include "file.h"
#include <cstdint>
#include <iostream>

void base::fix_bilibili_uwp_video(base::Path const &video_path)
{
	std::shared_ptr<base::Stream> source_video = base::file::OpenReadOnly(video_path);

	{
		// 视频开头有 3 个 0xff 垃圾数据，需要丢弃。
		uint8_t discarded_datas[3];
		source_video->Read(base::Span{discarded_datas, sizeof(discarded_datas)});
	}

	base::Path out_dir = video_path.ParentPath();
	base::Path out_video_path = out_dir + "fixed_" + video_path.LastName();
	std::cout << "输出文件：" << out_video_path << std::endl;
}
