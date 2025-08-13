#pragma once
#include "base/container/Range.h"
#include "base/filesystem/filesystem.h"
#include "base/filesystem/IMemoryMapFile.h"
#include "base/filesystem/Path.h"
#include "base/stream/Span.h"
#include <cstdint>
#include <iostream>
#include <string>

#if HAS_THREAD

namespace base
{
	namespace test
	{
		inline void TestMemoryMapFile()
		{
			constexpr uint8_t datas[128] = {0, 1, 2, 3, 4, 5, 6};
			constexpr int64_t datas_size = sizeof(datas);
			base::Path path{"test.map"};

			// 写入
			{
				std::shared_ptr<base::memory_map_file::IMemoryMapFile> mf = base::memory_map_file::OpenOrCreate(path);
				base::Span file_memory_span = mf->Map(base::Range{0, datas_size});
				file_memory_span.CopyFrom(base::ReadOnlySpan{datas, sizeof(datas)});
			}

			// 读取
			// 内存映射文件在文件关闭后能够保存数据，相当于一块非易失性的内存，所以读取的数据应该和写入的数据一样。
			{
				std::shared_ptr<base::memory_map_file::IMemoryMapFile> mf = base::memory_map_file::OpenOrCreate(path);
				base::Span file_memory_span = mf->Map(base::Range{0, datas_size});

				for (int64_t i = 0; i < datas_size; i++)
				{
					std::cout << std::to_string(file_memory_span[i]) << ", ";
					if ((i + 1) % 40 == 0)
					{
						std::cout << std::endl;
					}
				}

				std::cout << std::endl;
			}

			{
				base::filesystem::Remove(path);
				std::cout << "删除 " << path << std::endl;
			}
		}

	} // namespace test
} // namespace base

#endif // HAS_THREAD
