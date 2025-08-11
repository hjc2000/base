#pragma once
#include "base/container/Range.h"
#include "Path.h"
#include <cstdint>
#include <memory>

namespace base
{
	namespace memory_map_file
	{
		class IMemoryMapFile
		{
		public:
			///
			/// @brief 将文件指定范围映射为进程地址空间中的内存块。
			///
			/// @param range
			/// @return
			///
			virtual void *Map(base::Range const &range) = 0;

			///
			/// @brief 调整文件大小。
			///
			/// @param size
			///
			virtual void Resize(int64_t size) = 0;
		};

		///
		/// @brief 打开或创建一个内存映射文件。
		///
		/// @param path
		/// @return
		///
		std::shared_ptr<base::memory_map_file::IMemoryMapFile> OpenOrCreate(base::Path const &path);

	} // namespace memory_map_file
} // namespace base
