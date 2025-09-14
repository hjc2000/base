#pragma once
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

	} // namespace flash
} // namespace base
