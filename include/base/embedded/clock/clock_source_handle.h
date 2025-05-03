#pragma once
#include "base/unit/MHz.h"
#include <cstdint>
#include <map>
#include <memory>
#include <string>

namespace base
{
	namespace clock
	{
		class clock_source_handle;

		std::shared_ptr<base::clock::clock_source_handle> open(std::string const &name);

		///
		/// @brief 获取时钟源的频率。
		///
		/// @param h
		/// @return
		///
		base::MHz frequency(clock_source_handle &h);

		///
		/// @brief 配置时钟源。
		///
		/// @param h
		///
		void configure(clock_source_handle &h);

		///
		/// @brief 配置时钟源。
		///
		/// @param h
		///
		/// @param channel_factor_map 储存着各个通道的分频或倍频系数的 map. 其中 key 是通道的
		/// ID, value 是系数。
		///
		void configure(clock_source_handle &h,
					   std::map<uint32_t, uint32_t> const &channel_factor_map);

	} // namespace clock
} // namespace base
