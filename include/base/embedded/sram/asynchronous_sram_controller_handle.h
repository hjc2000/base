#pragma once
#include "base/embedded/sram/asynchronous_sram_timing.h"
#include "ISRAMTimingProvider.h"
#include <cstdint>
#include <memory>

namespace base
{
	namespace asynchronous_sram
	{
		class asynchronous_sram_controller_handle;

		std::shared_ptr<base::asynchronous_sram::asynchronous_sram_controller_handle> open(uint32_t id);

		void msp_initialize_callback(uint32_t id);

		///
		/// @brief 初始化 SRAM 控制器。
		///
		/// @param self
		/// @param timing_provider
		///
		void initialize(base::asynchronous_sram::asynchronous_sram_controller_handle &self,
						base::asynchronous_sram::ISRAMTimingProvider const &timing_provider);

		///
		/// @brief 初始化 SRAM 控制器成功后可以调用本方法获取正在应用中的时序。
		///
		/// @param self
		/// @return
		///
		base::asynchronous_sram::asynchronous_sram_timing timing(base::asynchronous_sram::asynchronous_sram_controller_handle &self);

	} // namespace asynchronous_sram
} // namespace base
