#include "W9825G6KH_6_Operator.h" // IWYU pragma: keep
#include "base/embedded/sdram/chip/w9825g6kh_6/TimingProvider.h"
#include "base/task/delay.h"
#include "ModeRegister.h"

void base::sdram::chip::w9825g6kh_6::W9825G6KH_6_Operator::InitializeAsReadBurstMode(std::string const &clock_source_name,
																					 uint32_t divider)
{
	_controller.InitializeAsReadBurstMode(clock_source_name,
										  divider,
										  base::sdram::chip::w9825g6kh_6::TimingProvider{},
										  base::sdram::BankCount{4},
										  base::sdram::RowBitCount{13},
										  base::sdram::ColumnBitCount{9},
										  base::sdram::DataWidth{16},
										  base::sdram::ReadBurstLength{1});

	// SDRAM控制器初始化完成以后还需要按照如下顺序初始化SDRAM
	base::task::Delay(std::chrono::microseconds{500});
	_controller.SendPrechargeAllCommand();
	_controller.SendAutoRefreshCommand(8);

	base::sdram::chip::w9825g6kh_6::ModeRegister reg{};
	reg.SetReadingBurstLength(1);
	reg.SetReadingBurstMode(base::sdram::chip::w9825g6kh_6::ReadingBurstMode::Sequential);
	reg.SetCasLatency(_controller.Timing().cas_latency());
	reg.SetWritingBurstMode(base::sdram::chip::w9825g6kh_6::WritingBurstMode::Single);
	_controller.WriteModeRegister(reg.Value());
}
