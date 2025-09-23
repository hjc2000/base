#pragma once
#include "base/embedded/sram/asynchronous_sram_timing.h"
#include "base/stream/Span.h"
#include <cstdint>
#include <memory>

namespace base
{
	namespace asynchronous_sram
	{
		class asynchronous_sram_controller_handle;

		std::shared_ptr<base::asynchronous_sram::asynchronous_sram_controller_handle> open(uint32_t id);

		///
		/// @brief 初始化 SRAM 控制器。
		///
		/// @param self
		/// @param timing 时序。
		///
		void initialize(base::asynchronous_sram::asynchronous_sram_controller_handle &self,
						base::asynchronous_sram::asynchronous_sram_timing const &timing);

		///
		/// @brief SRAM 控制器所管理的内存段。
		///
		/// @note 实际可用的空间由实际的 SRAM 大小决定。这里返回的内存段只是 SRAM 控制器所管理的范围。
		///
		/// @param self
		/// @return
		///
		base::Span span(base::asynchronous_sram::asynchronous_sram_controller_handle &self);

		///
		/// @brief SRAM 的底层初始化回调。
		///
		/// @note 此函数由板级支持的人员实现，外设支持的人员不负责。
		///
		/// @note 在初始化 SRAM 控制器时，控制器会回调此函数。在这里执行一些底层的初始化，例如 GPIO 初始化。
		///
		/// @note 需自行初始化 SRAM 控制器的 GPIO 引脚。 SRAM 控制器无法负责 GPIO 引脚的初始化。
		/// 因为：
		/// 	@li 即使是同一个外设的同一个信号，也可以分配到不同的 GPIO 引脚上。
		/// 	@li SRAM 芯片各种各样，所需的地址线和数据线个数也不一样。
		/// 这部分工作需要结合原理图完成。
		///
		/// @param id SRAM 控制器的 ID, 与 open 函数中传入的一致。
		///
		void msp_initialize_callback(uint32_t id);

	} // namespace asynchronous_sram
} // namespace base
