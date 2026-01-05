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

			/* #region Frequency */

			///
			/// @brief 获取时钟源的频率。
			///
			/// @return
			///
			base::unit::MHz Frequency()
			{
				return base::clock::frequency(*_handle);
			}

			///
			/// @brief 获取指定输出通道的频率。
			///
			/// @param output_channel_name
			/// @return
			///
			base::unit::MHz Frequency(std::string const &output_channel_name)
			{
				return base::clock::frequency(*_handle, output_channel_name);
			}

			/* #endregion */

			/* #region Configure */

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
			/// @param input_divider 对输入的时钟源的分频系数。
			///
			void Configure(uint32_t input_divider)
			{
				base::clock::configure(*_handle, input_divider);
			}

			///
			/// @brief 配置时钟源。
			///
			/// @param channel_factor_map 储存着各个通道的分频或倍频系数的 map. 其中 key 是通道的
			/// 名称，value 是系数。
			///
			void Configure(std::map<std::string, uint32_t> const &channel_factor_map)
			{
				base::clock::configure(*_handle, channel_factor_map);
			}

			///
			/// @brief 配置时钟源。
			///
			/// @param input_channel_name 时钟源具有多个输入通道可供选择。选择一个。
			///
			void Configure(std::string const &input_channel_name)
			{
				base::clock::configure(*_handle,
									   input_channel_name);
			}

			///
			/// @brief 配置时钟源。
			///
			/// @param input_channel_name 时钟源具有多个输入通道可供选择。选择一个。
			/// @param input_divider 对输入的时钟源的分频系数。
			///
			void Configure(std::string const &input_channel_name,
						   uint32_t input_divider)
			{
				base::clock::configure(*_handle,
									   input_channel_name,
									   input_divider);
			}

			///
			/// @brief 配置时钟源。
			///
			/// @param input_channel_name 时钟源具有多个输入通道可供选择。选择一个。
			///
			/// @param channel_factor_map 储存着各个通道的分频或倍频系数的 map. 其中 key 是通道的
			/// 名称，value 是系数。
			///
			void Configure(std::string const &input_channel_name,
						   std::map<std::string, uint32_t> const &channel_factor_map)
			{
				base::clock::configure(*_handle,
									   input_channel_name,
									   channel_factor_map);
			}

			/* #endregion */

			///
			/// @brief 设置为旁路模式。
			///
			/// @param bypass_input_frequency 旁路的输入频率。
			///
			void ConfigureAsBypassMode(base::unit::MHz const &bypass_input_frequency)
			{
				base::clock::configure_as_bypass_mode(*_handle,
													  bypass_input_frequency);
			}

			///
			/// @brief 关闭此时钟源。
			///
			///
			void TurnOff()
			{
				base::clock::turn_off(*_handle);
			}
		};

	} // namespace clock
} // namespace base
