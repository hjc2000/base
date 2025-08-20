#pragma once
#include "asynchronous_sram_controller_handle.h"
#include <cstdint>

namespace base
{
	namespace asynchronous_sram
	{
		///
		/// @brief 异步 SRAM 控制器。
		///
		/// @note 异步 SRAM 不需要主机提供时钟信号，但是需要主机接口支持 WAIT 信号。
		///
		class AsynchronousSramController
		{
		private:
			std::shared_ptr<base::asynchronous_sram::asynchronous_sram_controller_handle> _handle;

		public:
			AsynchronousSramController(uint32_t id)
			{
				_handle = base::asynchronous_sram::open(id);
			}

			void Initialize(base::asynchronous_sram::ISRAMTimingProvider const &timing_provider)
			{
				base::asynchronous_sram::initialize(*_handle, timing_provider);
			}
		};

	} // namespace asynchronous_sram
} // namespace base
