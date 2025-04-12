#pragma once
#include "base/string/Json.h"
#include "base/unit/MHz.h"
#include "base/unit/Nanoseconds.h"

namespace base
{
	namespace sdram
	{
		///
		/// @brief SDRAM 时序。
		///
		///
		class sdram_timing :
			public base::IJsonSerializable
		{
		public:
			int64_t _row_count = 0;
			base::MHz _clock_frequency{};
			base::Nanoseconds _t_rsc{};
			base::Nanoseconds _t_xsr{};
			base::Nanoseconds _t_ras{};
			base::Nanoseconds _t_rc{};
			base::Nanoseconds _t_wr{};
			base::Nanoseconds _t_rp{};
			base::Nanoseconds _t_rcd{};
			base::Nanoseconds _t_ref{};
			int _cas_latency = 0;

			///
			/// @brief SDRAM 的行数。
			///
			/// @return
			///
			int64_t row_count() const
			{
				return _row_count;
			}

			///
			/// @brief 时钟信号频率。
			///
			/// @return base::MHz
			///
			base::MHz clock_frequency() const
			{
				return _clock_frequency;
			}

			///
			/// @brief 时钟信号周期。
			///
			/// @return base::Nanoseconds
			///
			base::Nanoseconds clock_period() const
			{
				return base::Nanoseconds{_clock_frequency};
			}

			///
			/// @brief 模式寄存器设置延迟。
			///
			/// @note 设置模式寄存器后要等待这么长时间才可以进行下一个命令。
			/// 	@li 设置模式寄存器后要等待 t_rsc 后才可以进行下一次的设置模式寄存器。
			/// 	@li 设置模式寄存器后要等待 t_rsc 后才可以发送行激活命令。
			/// 	@li 设置模式寄存器后要等待 t_rsc 后才可以发送自动刷新命令。
			///
			/// @return
			///
			base::Nanoseconds t_rsc() const
			{
				return _t_rsc;
			}

			int t_rsc_clock_count() const
			{
				base::Fraction value{_t_rsc / clock_period()};
				return static_cast<int>(value.Ceil());
			}

			///
			/// @brief 退出自刷新模式的时间。
			///
			/// @note 注意：“自刷新” 不是 “自动刷新”
			///
			/// @return
			///
			base::Nanoseconds t_xsr() const
			{
				return _t_xsr;
			}

			int t_xsr_clock_count() const
			{
				base::Fraction value{_t_xsr / clock_period()};
				return static_cast<int>(value.Ceil());
			}

			///
			/// @brief 从行激活到预充电的时间。
			///
			/// 	@note 激活一行后，至少保持 T_RAS 后才能发送预充电命令关闭这行。例如在写的时候，如果 SDRAM
			/// 	还没来得及储存好写入的数据，就直接发送预充电命令关闭这行，数据可能会写失败。
			///
			/// @return
			///
			base::Nanoseconds t_ras() const
			{
				return _t_ras;
			}

			int t_ras_clock_count() const
			{
				base::Fraction value{_t_ras / clock_period()};
				return static_cast<int>(value.Ceil());
			}

			///
			/// @brief 行循环时间。
			/// 	@note 本次激活一行到下一次激活一行的时间间隔。
			///
			/// @return
			///
			base::Nanoseconds t_rc() const
			{
				return _t_rc;
			}

			int t_rc_clock_count() const
			{
				base::Fraction value{_t_rc / clock_period()};
				return static_cast<int>(value.Ceil());
			}

			///
			/// @brief 写恢复时间。
			///
			/// 	@note 发送写命令后，至少将信号保持 T_WR 后才能撤掉信号进入下一个命令。下一个命令可以是写命令，
			/// 	也可以是预充电命令。如果使用了自动预充电的写模式，则 SDRAM 内部会自己在 T_WR 后进行预充电。
			///
			/// @return
			///
			base::Nanoseconds t_wr() const
			{
				return _t_wr;
			}

			int t_wr_clock_count() const
			{
				base::Fraction value{_t_wr / clock_period()};
				return static_cast<int>(value.Ceil());
			}

			///
			/// @brief 预充电命令后的延迟。
			///
			/// 	@note 发送预充电命令后要等待 T_RP 才可以进行下一个命令。如果使用了自动预充电读写模式，
			/// 	也是要在 SDRAM 内部自动预充电后再继续等待 T_RP.
			///
			/// @return
			///
			base::Nanoseconds t_rp() const
			{
				return _t_rp;
			}

			int t_rp_clock_count() const
			{
				base::Fraction value{_t_rp / clock_period()};
				return static_cast<int>(value.Ceil());
			}

			///
			/// @brief 行到列时间。
			///
			/// 	@note 读写数据需要先发送行激活命令激活其中一行，然后发送读写命令选中其中一列
			/// 	（列地址信号是读写命令的一部分）。发送行激活命令后要 T_RCD 后才能发送读写命令。
			///
			/// @return
			///
			base::Nanoseconds t_rcd() const
			{
				return _t_rcd;
			}

			int t_rcd_clock_count() const
			{
				base::Fraction value{_t_rcd / clock_period()};
				return static_cast<int>(value.Ceil());
			}

			///
			/// @brief 自动刷新时间。
			///
			/// 	@note 至少这么长时间刷新一次所有行。如果超过这么长时间没有刷新完所有行，数据有可能丢失。
			///
			/// 	@note T_REF 指示了 SDRAM 内部电容能够将电压保持在安全范围的时间。
			///
			/// 	@note 发送一次自动刷新命令会刷新一行。SDRAM 内部有一个计数器，每次发送自动刷新命令都会
			/// 	刷新计数器的当前行然后递增计数器。如果有 8192 行，则必须在 T_REF 时间内发送超过 8192 次
			/// 	自动刷新命令，这样才能保证数据安全。
			///
			/// @return
			///
			base::Nanoseconds t_ref() const
			{
				return _t_ref;
			}

			int t_ref_clock_count() const
			{
				base::Fraction value{_t_ref / clock_period()};
				return static_cast<int>(value.Ceil());
			}

			///
			/// @brief 发送自动刷新命令的时间间隔。
			/// @return
			///
			base::Nanoseconds auto_refresh_command_period() const
			{
				return t_ref() / row_count();
			}

			///
			/// @brief 每隔多少个时钟周期要发送一次自动刷新命令。
			/// @return
			///
			int auto_refresh_command_clock_count() const
			{
				base::Fraction value{auto_refresh_command_period() / clock_period()};
				return static_cast<int>(value.Ceil());
			}

			///
			/// @brief 发送读命令后要等待多少个 CLK 信号的周期 SDRAM 才能将数据输出到数据总线上。
			///
			/// @return
			///
			int cas_latency() const
			{
				return _cas_latency;
			}

			///
			/// @brief 序列化为 json
			/// @return
			///
			virtual base::Json ToJson() const override;
		};

	} // namespace sdram
} // namespace base
