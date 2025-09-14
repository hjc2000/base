#pragma once
#include "base/stream/Span.h"
#include <cstdint>
#include <memory>

namespace base
{
	namespace flash
	{
		class flash_handle;

		std::shared_ptr<base::flash::flash_handle> open(uint32_t id);

		void initialize(base::flash::flash_handle &self);

		///
		/// @brief 一个扇区的大小。单位：字节。
		///
		/// @note 擦除必须以扇区为单位，至少擦除一个扇区。
		///
		/// @param self
		/// @return
		///
		int64_t sector_size(base::flash::flash_handle &self);

		///
		/// @brief 扇区数量。
		///
		/// @param self
		/// @return
		///
		int64_t sector_count(base::flash::flash_handle &self);

		///
		/// @brief 读取的最小粒度。单位：字节。
		///
		int64_t reading_size(base::flash::flash_handle &self);

		///
		/// @brief 编程的最小粒度。单位：字节。
		///
		/// @param self
		/// @return
		///
		int64_t program_size(base::flash::flash_handle &self);

		///
		/// @brief 擦除一个扇区。
		///
		/// @param self
		/// @param sector_index
		///
		void erase(base::flash::flash_handle &self, int64_t sector_index);

		///
		/// @brief 读取一个扇区内的数据。
		///
		/// @param self
		/// @param sector_index 扇区索引。
		/// @param offset 扇区内地址偏移量。即要读取的起始位置相对于扇区起始偏移了多少字节。
		/// @param span 读出的数据放到此 span 中。
		///
		/// @note 此函数禁止跨扇区读取。例如指定的起始地址离扇区结束只有 256 字节，span
		/// 的大小就不能超过 256 字节。
		///
		void read_sector(base::flash::flash_handle &self,
						 int64_t sector_index,
						 int64_t offset,
						 base::Span const &span);

	} // namespace flash
} // namespace base
