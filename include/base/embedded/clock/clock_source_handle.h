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
		/// @brief 获取指定输出通道的频率。
		///
		/// @param h
		/// @param output_channel_name
		/// @return
		///
		base::MHz frequency(clock_source_handle &h, std::string const &output_channel_name);

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
		/// 名称，value 是系数。
		///
		void configure(clock_source_handle &h,
					   std::map<std::string, uint32_t> const &channel_factor_map);

		///
		/// @brief 设置为旁路模式。
		///
		/// @param h
		/// @param bypass_input_frequency 旁路的输入频率。
		///
		void configure_as_bypass_mode(clock_source_handle &h,
									  base::MHz const &bypass_input_frequency);

		///
		/// @brief 关闭此时钟源。
		///
		/// @param h
		///
		void turn_off(clock_source_handle &h);

	} // namespace clock
} // namespace base
