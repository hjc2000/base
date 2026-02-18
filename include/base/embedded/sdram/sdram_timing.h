#pragma once
#include "base/string/Json.h"
#include "base/unit/MHz.h"
#include "base/unit/Nanosecond.h"
#include <cstdint>

namespace base::sdram
{
	///
	/// @brief SDRAM 时序。
	///
	///
	class sdram_timing final :
		public base::IJsonSerializable
	{
	private:
		int64_t _row_count = 0;
		base::unit::MHz _clock_frequency{};
		base::unit::Nanosecond _t_rsc{};
		base::unit::Nanosecond _t_xsr{};
		base::unit::Nanosecond _t_ras{};
		base::unit::Nanosecond _t_rc{};
		base::unit::Nanosecond _t_wr{};
		base::unit::Nanosecond _t_rp{};
		base::unit::Nanosecond _t_rcd{};
		base::unit::Nanosecond _t_ref{};
		uint32_t _cas_latency = 2;

	public:
		///
		/// @brief SDRAM 的行数。
		///
		/// @return
		///
		int64_t row_count() const
		{
			return _row_count;
		}

		void set_row_count(int64_t value)
		{
			_row_count = value;
		}

		/* #region 时钟信号 */

		///
		/// @brief 时钟信号频率。
		///
		/// @return
		///
		base::unit::MHz clock_frequency() const
		{
			return _clock_frequency;
		}

		///
		/// @brief 设置时钟信号频率。
		///
		/// @param value
		///
		void set_clock_frequency(base::unit::MHz const &value)
		{
			_clock_frequency = value;
		}

		///
		/// @brief 时钟信号周期。
		///
		/// @return
		///
		base::unit::Nanosecond clock_cycle() const
		{
			return base::unit::Nanosecond{_clock_frequency};
		}

		///
		/// @brief 设置时钟信号周期。
		///
		/// @param value
		///
		void set_clock_cycle(base::unit::Nanosecond const &value)
		{
			_clock_frequency = base::unit::MHz{value};
		}

		/* #endregion */

		/* #region t_rsc */

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
		base::unit::Nanosecond t_rsc() const
		{
			return _t_rsc;
		}

		void set_t_rsc(base::unit::Nanosecond const &value)
		{
			_t_rsc = value;
		}

		int t_rsc_clock_cycle_count() const
		{
			base::Fraction value{_t_rsc / clock_cycle()};
			return static_cast<int>(value.Ceil());
		}

		/* #endregion */

		/* #region t_xsr */

		///
		/// @brief 退出自刷新模式的时间。
		///
		/// @note 注意：“自刷新” 不是 “自动刷新”
		///
		/// @return
		///
		base::unit::Nanosecond t_xsr() const
		{
			return _t_xsr;
		}

		void set_t_xsr(base::unit::Nanosecond const &value)
		{
			_t_xsr = value;
		}

		int t_xsr_clock_cycle_count() const
		{
			base::Fraction value{_t_xsr / clock_cycle()};
			return static_cast<int>(value.Ceil());
		}

		/* #endregion */

		/* #region t_ras */

		///
		/// @brief 从行激活到预充电的时间。
		///
		/// @note 激活一行后，至少保持 T_RAS 后才能发送预充电命令关闭这行。例如在写的时候，
		/// 如果 SDRAM 还没来得及储存好写入的数据，就直接发送预充电命令关闭这行，数据可能会写失败。
		///
		/// @return
		///
		base::unit::Nanosecond t_ras() const
		{
			return _t_ras;
		}

		void set_t_ras(base::unit::Nanosecond const &value)
		{
			_t_ras = value;
		}

		int t_ras_clock_cycle_count() const
		{
			base::Fraction value{_t_ras / clock_cycle()};
			return static_cast<int>(value.Ceil());
		}

		/* #endregion */

		/* #region t_rc */

		///
		/// @brief 行循环时间。
		/// 	@note 本次激活一行到下一次激活一行的时间间隔。
		///
		/// @return
		///
		base::unit::Nanosecond t_rc() const
		{
			return _t_rc;
		}

		void set_t_rc(base::unit::Nanosecond const &value)
		{
			_t_rc = value;
		}

		int t_rc_clock_cycle_count() const
		{
			base::Fraction value{_t_rc / clock_cycle()};
			return static_cast<int>(value.Ceil());
		}

		/* #endregion */

		/* #region t_wr */

		///
		/// @brief 写恢复时间。
		///
		/// 	@note 发送写命令后，至少将信号保持 T_WR 后才能撤掉信号进入下一个命令。下一个命令可以是写命令，
		/// 	也可以是预充电命令。如果使用了自动预充电的写模式，则 SDRAM 内部会自己在 T_WR 后进行预充电。
		///
		/// @return
		///
		base::unit::Nanosecond t_wr() const
		{
			return _t_wr;
		}

		void set_t_wr(base::unit::Nanosecond const &value)
		{
			_t_wr = value;
		}

		int t_wr_clock_cycle_count() const
		{
			base::Fraction value{_t_wr / clock_cycle()};
			return static_cast<int>(value.Ceil());
		}

		/* #endregion */

		/* #region t_rp */

		///
		/// @brief 预充电命令后的延迟。
		///
		/// 	@note 发送预充电命令后要等待 T_RP 才可以进行下一个命令。如果使用了自动预充电读写模式，
		/// 	也是要在 SDRAM 内部自动预充电后再继续等待 T_RP.
		///
		/// @return
		///
		base::unit::Nanosecond t_rp() const
		{
			return _t_rp;
		}

		void set_t_rp(base::unit::Nanosecond const &value)
		{
			_t_rp = value;
		}

		int t_rp_clock_cycle_count() const
		{
			base::Fraction value{_t_rp / clock_cycle()};
			return static_cast<int>(value.Ceil());
		}

		/* #endregion */

		/* #region t_rcd */

		///
		/// @brief 行到列时间。
		///
		/// 	@note 读写数据需要先发送行激活命令激活其中一行，然后发送读写命令选中其中一列
		/// 	（列地址信号是读写命令的一部分）。发送行激活命令后要 T_RCD 后才能发送读写命令。
		///
		/// @return
		///
		base::unit::Nanosecond t_rcd() const
		{
			return _t_rcd;
		}

		void set_t_rcd(base::unit::Nanosecond const &value)
		{
			_t_rcd = value;
		}

		int t_rcd_clock_cycle_count() const
		{
			base::Fraction value{_t_rcd / clock_cycle()};
			return static_cast<int>(value.Ceil());
		}

		/* #endregion */

		/* #region t_ref */

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
		base::unit::Nanosecond t_ref() const
		{
			return _t_ref;
		}

		void set_t_ref(base::unit::Nanosecond const &value)
		{
			_t_ref = value;
		}

		int t_ref_clock_cycle_count() const
		{
			base::Fraction value{_t_ref / clock_cycle()};
			return static_cast<int>(value.Ceil());
		}

		///
		/// @brief 发送自动刷新命令的时间间隔。
		/// @return
		///
		base::unit::Nanosecond auto_refresh_command_period() const
		{
			return t_ref() / row_count();
		}

		///
		/// @brief 每隔多少个时钟周期要发送一次自动刷新命令。
		/// @return
		///
		int auto_refresh_command_clock_cycle_count() const
		{
			base::Fraction value{auto_refresh_command_period() / clock_cycle()};
			return static_cast<int>(value.Ceil());
		}

		/* #endregion */

		///
		/// @brief 发送读命令后要等待多少个 CLK 信号的周期 SDRAM 才能将数据输出到数据总线上。
		///
		/// @return
		///
		uint32_t cas_latency() const
		{
			return _cas_latency;
		}

		void set_cas_latency(uint32_t value)
		{
			_cas_latency = value;
		}

		///
		/// @brief 序列化为 json
		/// @return
		///
		virtual base::Json ToJson() const override
		{
			base::Json root{
				{"row_count", row_count()},
				{"clock_frequency", clock_frequency().ToString()},
				{"clock_cycle", clock_cycle().ToString()},
				{"t_rsc_clock_cycle_count", t_rsc_clock_cycle_count()},
				{"t_xsr_clock_cycle_count", t_xsr_clock_cycle_count()},
				{"t_ras_clock_cycle_count", t_ras_clock_cycle_count()},
				{"t_rc_clock_cycle_count", t_rc_clock_cycle_count()},
				{"t_wr_clock_cycle_count", t_wr_clock_cycle_count()},
				{"t_rp_clock_cycle_count", t_rp_clock_cycle_count()},
				{"t_rcd_clock_cycle_count", t_rcd_clock_cycle_count()},
				{"t_ref_clock_cycle_count", t_ref_clock_cycle_count()},
				{"auto_refresh_command_clock_cycle_count", auto_refresh_command_clock_cycle_count()},
				{"cas_latency", cas_latency()},
			};

			return root;
		}
	};

} // namespace base::sdram
