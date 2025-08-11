#pragma once
#include "base/container/Range.h"
#include "base/stream/Span.h"
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
			virtual base::Span Map(base::Range const &range) = 0;

			///
			/// @brief 取消映射。
			///
			/// @param address 传入 Map 方法返回的 base::Span 的 Buffer 属性。
			///
			virtual void UnMap(uint8_t *address) = 0;

			///
			/// @brief 取消所有映射。
			///
			///
			virtual void UnMapAll() = 0;

			///
			/// @brief 调整文件大小。
			///
			/// @param size
			///
			virtual void Resize(int64_t size) = 0;

			///
			/// @brief 关闭内存映射文件。
			///
			///
			virtual void Close() = 0;
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
