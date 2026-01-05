#pragma once
#include "base/embedded/sdram/ISDRAMTimingProvider.h"
#include "base/stream/Span.h"
#include "parameter.h"
#include <cstdint>
#include <memory>
#include <string>

namespace base::sdram
{
	class sdram_controller_handle;

	///
	/// @brief 打开指定的 SDRAM 控制器。
	///
	/// @param id
	///
	/// @return
	///
	std::shared_ptr<base::sdram::sdram_controller_handle> open(uint32_t id);

	///
	/// @brief 将 SDRAM 控制器初始化为读突发模式。写不突发。
	///
	/// @param h
	/// @param clock_source_name
	/// @param divider
	/// @param timing_provider
	/// @param bank_count
	/// @param row_bit_count
	/// @param column_bit_count
	/// @param data_width
	/// @param read_burst_length
	///
	void initialize_as_read_burst_mode(base::sdram::sdram_controller_handle &h,
									   std::string const &clock_source_name,
									   uint32_t divider,
									   base::sdram::ISDRAMTimingProvider const &timing_provider,
									   base::sdram::BankCount const &bank_count,
									   base::sdram::RowBitCount const &row_bit_count,
									   base::sdram::ColumnBitCount const &column_bit_count,
									   base::sdram::DataWidth const &data_width,
									   base::sdram::ReadBurstLength const &read_burst_length);

	/* #region 控制命令 */

	///
	/// @brief 发送：“预充电所有 BANK” 的命令。
	///
	/// @param h
	///
	void send_precharge_all_command(base::sdram::sdram_controller_handle &h);

	///
	/// @brief 发送自动刷新命令。
	///
	/// @param h
	///
	void send_auto_refresh_command(base::sdram::sdram_controller_handle &h);

	///
	/// @brief 发送指定次数的自动刷新命令。
	///
	/// @param h
	/// @param refresh_times
	///
	void send_auto_refresh_command(base::sdram::sdram_controller_handle &h, int refresh_times);

	///
	/// @brief 写模式寄存器。
	///
	/// @param h
	/// @param value
	///
	void write_mode_register(base::sdram::sdram_controller_handle &h, uint32_t value);

	/* #endregion */

	///
	/// @brief 控制器被初始化后所使用的时序。
	///
	/// @param h
	/// @return
	///
	base::sdram::sdram_timing const &timing(base::sdram::sdram_controller_handle &h);

	///
	/// @brief 此 SDRAM 控制器所管理的内存段。打开 SDRAM 后，对着这个地址区域读写数据即可读写 SDRAM.
	///
	/// @warning 注意，以实际的 SDRAM 芯片的大小为准。本控制器可能可以管理很大的区域，但是 SDRAM 芯片
	/// 实际上没有这么大。
	///
	/// @param h
	///
	/// @return
	///
	base::Span span(base::sdram::sdram_controller_handle &h);

	///
	/// @brief SDRAM 控制器的底层初始化回调。
	///
	/// @note 此函数由板级支持的人员实现，外设支持的人员不负责。
	///
	/// @note 在初始化 SDRAM 控制器时，控制器会回调此函数。在这里执行一些底层的初始化，例如 GPIO 初始化。
	///
	/// @note 需自行初始化 SDRAM 控制器的 GPIO 引脚。SDRAM 控制器无法负责 GPIO 引脚的初始化。
	/// 因为：
	/// 	@li 即使是同一个外设的同一个信号，也可以分配到不同的 GPIO 引脚上。
	/// 	@li SDRAM 芯片各种各样，所需的地址线和数据线个数也不一样。
	/// 这部分工作需要结合原理图完成。
	///
	/// @param id SDRAM 控制器的 ID, 与 open 函数中传入的 ID 是同一个。
	///
	void msp_initialize_callback(uint32_t id);

} // namespace base::sdram
