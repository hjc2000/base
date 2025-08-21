#pragma once
#include "asynchronous_sram_controller_handle.h"
#include "base/stream/Span.h"
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

			///
			/// @brief 初始化 SRAM 控制器。
			///
			/// @param timing_provider
			///
			void Initialize(base::asynchronous_sram::ISRAMTimingProvider const &timing_provider)
			{
				base::asynchronous_sram::initialize(*_handle, timing_provider);
			}

			///
			/// @brief 初始化 SRAM 控制器成功后可以调用本方法获取正在应用中的时序。
			///
			/// @return
			///
			base::asynchronous_sram::asynchronous_sram_timing Timing() const
			{
				return base::asynchronous_sram::timing(*_handle);
			}

			///
			/// @brief SRAM 控制器所管理的内存段。
			///
			/// @note 实际可用的空间由实际的 SRAM 大小决定。这里返回的内存段只是 SRAM 控制器所管理的范围。
			///
			/// @return
			///
			base::Span Span() const
			{
				return base::asynchronous_sram::span(*_handle);
			}
		};

	} // namespace asynchronous_sram
} // namespace base
