#pragma once
#include "base/embedded/sdram/chip/w9825g6kh_6/TimingProvider.h"
#include "base/embedded/sdram/SdramController.h"
#include "base/task/delay.h"
#include "ModeRegister.h"
#include <cstdint>

namespace base::sdram::chip::w9825g6kh_6
{
	///
	/// @brief W9825G6KH_6 芯片操作器。
	///
	class W9825G6KH_6_Operator final
	{
	private:
		base::sdram::SdramController _controller;

	public:
		///
		/// @brief 构造函数。
		/// @param controller 需要一个控制器来控制 SDRAM 芯片。
		///
		W9825G6KH_6_Operator(base::sdram::SdramController const &controller)
			: _controller(controller)
		{
		}

		/* #region 通用的打开方法 */

		///
		/// @brief 初始化 SDRAM.
		///
		/// @note 分为 2 步：
		/// 	@li 打开 SDRAM 控制器。
		/// 	@li 初始化 SDRAM 芯片。
		///
		void InitializeAsReadBurstMode(std::string const &clock_source_name,
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

		/* #endregion */

		/* #region 为特殊单片机定制的打开方法 */

		///
		/// @brief 为 stm32h743iit6 设计的打开函数。
		///
		/// @note 如果有些单片机实在太特殊，就为它单独设计一个函数。然后 SDRAM 句柄那边
		/// 也给它单独设计一个初始化函数。
		///
		void initialize_for_stm32h743iit6()
		{
			InitializeAsReadBurstMode("hclk3", 2);
		}

		/* #endregion */

		///
		/// @brief 此 SDRAM 的内存段。
		/// @return
		///
		base::Span Span() const
		{
			return base::Span{
				_controller.Span().Buffer(),
				std::min<int64_t>(32 * 1024 * 1024, _controller.Span().Size()),
			};
		}
	};

} // namespace base::sdram::chip::w9825g6kh_6
