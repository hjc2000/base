#include "W9825G6KH_6.h"
#include "base/peripheral/sdram/chip/W9825G6KH_6_TimingProvider.h"
#include "base/task/delay.h"

// SDRAM配置参数
#define SDRAM_MODEREG_BURST_LENGTH_1 ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2 ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4 ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8 ((uint16_t)0x0004)

#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED ((uint16_t)0x0008)

#define SDRAM_MODEREG_CAS_LATENCY_2 ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3 ((uint16_t)0x0030)

#define SDRAM_MODEREG_OPERATING_MODE_STANDARD ((uint16_t)0x0000)

#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE ((uint16_t)0x0200)

base::sdram::chip::W9825G6KH_6::W9825G6KH_6(base::sdram::SdramController const &controller)
	: _controller(controller)
{
}

void base::sdram::chip::W9825G6KH_6::Open()
{
	_controller.InitializeAsReadBurstMode(base::sdram::W9825G6KH_6_TimingProvider{},
										  base::sdram::BankCount{4},
										  base::sdram::RowBitCount{13},
										  base::sdram::ColumnBitCount{9},
										  base::sdram::DataWidth{16},
										  base::sdram::ReadBurstLength{1});

	// SDRAM控制器初始化完成以后还需要按照如下顺序初始化SDRAM
	base::task::Delay(std::chrono::microseconds{500});
	_controller.SendPrechargeAllCommand();
	_controller.SendAutoRefreshCommand(8);

	uint32_t cas_letency = SDRAM_MODEREG_CAS_LATENCY_2;
	if (_controller.Timing().cas_latency() == 3)
	{
		cas_letency = SDRAM_MODEREG_CAS_LATENCY_3;
	}

	/**
	 * 发送 “加载模式寄存器” 命令。
	 * 		@li 配置模式寄存器,SDRAM的bit0~bit2为指定突发访问的长度
	 * 		@li bit3为指定突发访问的类型，bit4~bit6为CAS值，bit7和bit8为运行模式
	 * 		@li bit9为指定的写突发模式，bit10和bit11位保留位
	 */
	uint32_t sdram_mod_register = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1 | // 设置突发长度:1(可以是1/2/4/8)
								  SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL |    // 设置突发类型:连续(可以是连续/交错)
								  cas_letency |                            // 设置CAS值:3(可以是2/3)
								  SDRAM_MODEREG_OPERATING_MODE_STANDARD |  // 设置操作模式:0,标准模式
								  SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;    // 设置突发写模式:1,单点访问

	_controller.WriteModeRegister(sdram_mod_register);
}

base::Span base::sdram::chip::W9825G6KH_6::Span() const
{
	return base::Span{_controller.Span().Buffer(), 32 * 1024 * 1024};
}
