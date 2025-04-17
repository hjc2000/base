#pragma once
#include "base/peripheral/sdram/chip/w9825g6kh_6/TimingProvider.h"
#include "base/peripheral/sdram/SdramController.h"
#include "base/task/delay.h"
#include "ModeRegister.h"
#include <cstdint>

namespace base
{
	namespace sdram
	{
		namespace chip
		{
			namespace w9825g6kh_6
			{
				class W9825G6KH_6
				{
				private:
					base::sdram::SdramController _controller;

				public:
					///
					/// @brief 构造函数。
					/// @param controller 需要一个控制器来控制 SDRAM 芯片。
					///
					W9825G6KH_6(base::sdram::SdramController const &controller)
						: _controller(controller)
					{
					}

					///
					/// @brief 打开 SDRAM.
					///
					/// @note 分为 2 步：
					/// 	@li 打开 SDRAM 控制器。
					/// 	@li 初始化 SDRAM 芯片。
					///
					void Open()
					{
						_controller.InitializeAsReadBurstMode(base::sdram::chip::w9825g6kh_6::TimingProvider{},
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

					///
					/// @brief 此 SDRAM 的内存段。
					/// @return
					///
					base::Span Span() const
					{
						return base::Span{
							_controller.Span().Buffer(),
							std::min<int32_t>(32 * 1024 * 1024, _controller.Span().Size()),
						};
					}
				};
			} // namespace w9825g6kh_6
		} // namespace chip
	} // namespace sdram
} // namespace base
