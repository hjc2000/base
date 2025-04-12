#pragma once
#include "base/string/Json.h"
#include "base/unit/MHz.h"
#include "base/unit/Nanoseconds.h"

namespace base
{
	namespace sdram
	{
		class sdram_timing :
			public base::IJsonSerializable
		{
		private:
			int64_t _row_count = 0;
			base::MHz _clock_frequency{};
			base::Nanoseconds _T_RSC{};
			base::Nanoseconds _T_XSR{};
			base::Nanoseconds _T_RAS{};
			base::Nanoseconds _T_RC{};
			base::Nanoseconds _T_WR{};
			base::Nanoseconds _T_RP{};
			base::Nanoseconds _T_RCD{};
			base::Nanoseconds _T_REF{};
			int _cas_latency = 0;

		public:
			sdram_timing(int64_t row_count,
						 base::MHz const &clock_frequency,
						 base::Nanoseconds const &T_RSC,
						 base::Nanoseconds const &T_XSR,
						 base::Nanoseconds T_RAS,
						 base::Nanoseconds T_RC,
						 base::Nanoseconds T_WR,
						 base::Nanoseconds T_RP,
						 base::Nanoseconds T_RCD,
						 base::Nanoseconds T_REF,
						 int cas_latency)
			{
				_row_count = row_count;
				_clock_frequency = clock_frequency;
				_T_RSC = T_RSC;
				_T_XSR = T_XSR;
				_T_RAS = T_RAS;
				_T_RC = T_RC;
				_T_WR = T_WR;
				_T_RP = T_RP;
				_T_RCD = T_RCD;
				_T_REF = T_REF;
				_cas_latency = cas_latency;
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
			/// 	@li 设置模式寄存器后要等待 T_RSC 后才可以进行下一次的设置模式寄存器。
			/// 	@li 设置模式寄存器后要等待 T_RSC 后才可以发送行激活命令。
			/// 	@li 设置模式寄存器后要等待 T_RSC 后才可以发送自动刷新命令。
			///
			/// @return
			///
			base::Nanoseconds T_RSC() const
			{
				return _T_RSC;
			}

			int T_RSC_CLK_Count() const
			{
				base::Fraction value{T_RSC() / clock_period()};
				return static_cast<int>(value.Ceil());
			}

			///
			/// @brief 退出自刷新模式的时间。
			///
			/// @note 注意：“自刷新” 不是 “自动刷新”
			///
			/// @return
			///
			base::Nanoseconds T_XSR() const
			{
				return _T_XSR;
			}

			int T_XSR_CLK_Count() const
			{
				base::Fraction value{T_XSR() / clock_period()};
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
			base::Nanoseconds T_RAS() const
			{
				return _T_RAS;
			}

			int T_RAS_CLK_Count() const
			{
				base::Fraction value{T_RAS() / clock_period()};
				return static_cast<int>(value.Ceil());
			}

			///
			/// @brief 行循环时间。
			/// 	@note 本次激活一行到下一次激活一行的时间间隔。
			///
			/// @return
			///
			base::Nanoseconds T_RC() const
			{
				return _T_RC;
			}

			int T_RC_CLK_Count() const
			{
				base::Fraction value{T_RC() / clock_period()};
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
			base::Nanoseconds T_WR() const
			{
				return _T_WR;
			}

			int T_WR_CLK_Count() const
			{
				base::Fraction value{T_WR() / clock_period()};
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
			base::Nanoseconds T_RP() const
			{
				return _T_RP;
			}

			int T_RP_CLK_Count() const
			{
				base::Fraction value{T_RP() / clock_period()};
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
			base::Nanoseconds T_RCD() const
			{
				return _T_RCD;
			}

			int T_RCD_CLK_Count() const
			{
				base::Fraction value{T_RCD() / clock_period()};
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
			base::Nanoseconds T_REF() const
			{
				return _T_REF;
			}

			int T_REF_CLK_Count() const
			{
				base::Fraction value{T_REF() / clock_period()};
				return static_cast<int>(value.Ceil());
			}

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
			/// @brief 发送自动刷新命令的时间间隔。
			/// @return
			///
			base::Nanoseconds auto_refresh_command_period() const
			{
				return T_REF() / row_count();
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
