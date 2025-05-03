#pragma once

#include "clock_source_handle.h"
#include <memory>
#include <string>

namespace base
{
	namespace clock
	{
		class ClockSource
		{
		private:
			std::shared_ptr<base::clock::clock_source_handle> _handle;

		public:
			ClockSource(std::string const &name)
			{
				_handle = base::clock::open(name);
			}

			///
			/// @brief 获取时钟源的频率。
			///
			/// @return
			///
			base::MHz Frequency()
			{
				return base::clock::frequency(*_handle);
			}

			///
			/// @brief 配置时钟源。
			///
			///
			void Configure()
			{
				base::clock::configure(*_handle);
			}

			///
			/// @brief 配置时钟源。
			///
			/// @param channel_factor_map 储存着各个通道的分频或倍频系数的 map. 其中 key 是通道的
			/// ID, value 是系数。
			///
			void Configure(std::map<uint32_t, uint32_t> const &channel_factor_map)
			{
				base::clock::configure(*_handle, channel_factor_map);
			}
		};
	} // namespace clock
} // namespace base
