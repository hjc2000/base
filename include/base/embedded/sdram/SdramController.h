#pragma once
#include "base/embedded/sdram/sdram_controller_handle.h"
#include <memory>

namespace base::sdram
{
	class SdramController
	{
	private:
		std::shared_ptr<base::sdram::sdram_controller_handle> _handle;

	public:
		SdramController(uint32_t id)
		{
			_handle = base::sdram::open(id);
		}

		///
		/// @brief 将 SDRAM 控制器初始化为读突发模式。写不突发。
		///
		/// @param clock_source_name
		/// @param divider
		/// @param timing_provider
		/// @param bank_count
		/// @param row_bit_count
		/// @param column_bit_count
		/// @param data_width
		/// @param read_burst_length
		///
		void InitializeAsReadBurstMode(std::string const &clock_source_name,
									   uint32_t divider,
									   base::sdram::ISDRAMTimingProvider const &timing_provider,
									   base::sdram::BankCount const &bank_count,
									   base::sdram::RowBitCount const &row_bit_count,
									   base::sdram::ColumnBitCount const &column_bit_count,
									   base::sdram::DataWidth const &data_width,
									   base::sdram::ReadBurstLength const &read_burst_length)
		{
			base::sdram::initialize_as_read_burst_mode(*_handle,
													   clock_source_name,
													   divider,
													   timing_provider,
													   bank_count,
													   row_bit_count,
													   column_bit_count,
													   data_width,
													   read_burst_length);
		}

		///
		/// @brief 发送：“预充电所有 BANK” 的命令。
		///
		///
		void SendPrechargeAllCommand()
		{
			base::sdram::send_precharge_all_command(*_handle);
		}

		///
		/// @brief 发送自动刷新命令。
		///
		///
		void SendAutoRefreshCommand()
		{
			base::sdram::send_auto_refresh_command(*_handle);
		}

		///
		/// @brief 发送指定次数的自动刷新命令。
		///
		/// @param refresh_times
		///
		void SendAutoRefreshCommand(int refresh_times)
		{
			base::sdram::send_auto_refresh_command(*_handle, refresh_times);
		}

		///
		/// @brief 写模式寄存器。
		///
		/// @param value
		///
		void WriteModeRegister(uint32_t value)
		{
			base::sdram::write_mode_register(*_handle, value);
		}

		///
		/// @brief 控制器被打开后所使用的时序。
		///
		/// @return
		///
		base::sdram::sdram_timing const &Timing() const
		{
			return base::sdram::timing(*_handle);
		}

		///
		/// @brief 此 SDRAM 控制器所管理的内存段。打开 SDRAM 后，对着这个地址区域读写数据即可读写 SDRAM.
		///
		/// @warning 注意，以实际的 SDRAM 芯片的大小为准。本控制器可能可以管理很大的区域，但是 SDRAM 芯片
		/// 实际上没有这么大。
		///
		/// @return
		///
		base::Span Span() const
		{
			return base::sdram::span(*_handle);
		}
	};

} // namespace base::sdram
