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

		/* #region frequency */

		///
		/// @brief 获取时钟源的频率。
		///
		/// @param self
		/// @return
		///
		base::unit::MHz frequency(base::clock::clock_source_handle &self);

		///
		/// @brief 获取指定输出通道的频率。
		///
		/// @param self
		/// @param output_channel_name
		/// @return
		///
		base::unit::MHz frequency(base::clock::clock_source_handle &self,
								  std::string const &output_channel_name);

		/* #endregion */

		/* #region configure */

		///
		/// @brief 配置时钟源。
		///
		/// @param self
		///
		void configure(base::clock::clock_source_handle &self);

		///
		/// @brief 配置时钟源。
		///
		/// @param self
		/// @param input_divider 对输入的时钟源的分频系数。
		///
		void configure(base::clock::clock_source_handle &self, uint32_t input_divider);

		///
		/// @brief 配置时钟源。
		///
		/// @param self
		///
		/// @param channel_factor_map 储存着各个通道的分频或倍频系数的 map. 其中 key 是通道的
		/// 名称，value 是系数。
		///
		void configure(base::clock::clock_source_handle &self,
					   std::map<std::string, uint32_t> const &channel_factor_map);

		///
		/// @brief 配置时钟源。
		///
		/// @param self
		/// @param input_channel_name 时钟源具有多个输入通道可供选择。选择一个。
		///
		void configure(base::clock::clock_source_handle &self,
					   std::string const &input_channel_name);

		///
		/// @brief 配置时钟源。
		///
		/// @param self
		/// @param input_channel_name 时钟源具有多个输入通道可供选择。选择一个。
		/// @param input_divider 对输入的时钟源的分频系数。
		///
		void configure(base::clock::clock_source_handle &self,
					   std::string const &input_channel_name,
					   uint32_t input_divider);

		///
		/// @brief 配置时钟源。
		///
		/// @param self
		///
		/// @param input_channel_name 时钟源具有多个输入通道可供选择。选择一个。
		///
		/// @param channel_factor_map 储存着各个通道的分频或倍频系数的 map. 其中 key 是通道的
		/// 名称，value 是系数。
		///
		void configure(base::clock::clock_source_handle &self,
					   std::string const &input_channel_name,
					   std::map<std::string, uint32_t> const &channel_factor_map);

		/* #endregion */

		///
		/// @brief 设置为旁路模式。
		///
		/// @param self
		/// @param bypass_input_frequency 旁路的输入频率。
		///
		void configure_as_bypass_mode(base::clock::clock_source_handle &self,
									  base::unit::MHz const &bypass_input_frequency);

		///
		/// @brief 关闭此时钟源。
		///
		/// @param self
		///
		void turn_off(base::clock::clock_source_handle &self);

	} // namespace clock
} // namespace base
