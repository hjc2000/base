#pragma once
#include "base/math/Fraction.h"
#include "base/string/Json.h"
#include "base/unit/MHz.h"
#include "base/unit/Nanosecond.h"

namespace base
{
	namespace asynchronous_sram
	{
		///
		/// @brief 异步的 SRAM 时序。
		///
		/// @note 异步 SRAM 不需要主机提供时钟信号，但是需要主机接口支持 WAIT 信号。
		///
		class asynchronous_sram_timing final :
			public base::IJsonSerializable
		{
		private:
			base::unit::MHz _clock_frequency{};
			base::unit::Nanosecond _address_setup_time{};
			base::unit::Nanosecond _address_hold_time{};
			base::unit::Nanosecond _data_setup_time{};
			base::unit::Nanosecond _bus_turn_around_time{};

		public:
			/* #region 时钟 */

			///
			/// @brief SRAM 控制器的时钟频率。
			///
			/// @return
			///
			base::unit::MHz clock_frequency() const
			{
				return _clock_frequency;
			}

			///
			/// @brief 设置 SRAM 控制器的时钟频率。
			///
			/// @param value
			///
			void set_clock_frequency(base::unit::MHz const &value)
			{
				_clock_frequency = value;
			}

			///
			/// @brief SRAM 控制器的时钟信号周期。
			///
			/// @return
			///
			base::unit::Nanosecond clock_cycle() const
			{
				return base::unit::Nanosecond{_clock_frequency};
			}

			///
			/// @brief 设置 SRAM 控制器的时钟信号周期。
			///
			/// @param value
			///
			void set_clock_cycle(base::unit::Nanosecond const &value)
			{
				_clock_frequency = base::unit::MHz{value};
			}

			/* #endregion */

			/* #region 地址建立时间 */

			///
			/// @brief 地址建立时间。
			///
			/// @return
			///
			base::unit::Nanosecond address_setup_time() const
			{
				return _address_setup_time;
			}

			///
			/// @brief 设置地址建立时间。
			///
			/// @param value
			///
			void set_address_setup_time(base::unit::Nanosecond const &value)
			{
				_address_setup_time = value;
			}

			///
			/// @brief 地址建立时间是多少个 SRAM 控制器的时钟周期。
			///
			/// @return
			///
			int address_setup_clock_cycle_count() const
			{
				base::Fraction value{_address_setup_time / clock_cycle()};
				return static_cast<int>(value.Ceil());
			}

			///
			/// @brief 设置地址建立时钟周期数。
			///
			/// @param value
			///
			void set_address_setup_clock_cycle_count(int value)
			{
				_address_setup_time = value * clock_cycle();
			}

			/* #endregion */

			/* #region 地址保持时间 */

			///
			/// @brief 地址保持时间。
			///
			/// @return
			///
			base::unit::Nanosecond address_hold_time() const
			{
				return _address_hold_time;
			}

			///
			/// @brief 设置地址保持时间。
			///
			/// @param value
			///
			void set_address_hold_time(base::unit::Nanosecond const &value)
			{
				_address_hold_time = value;
			}

			///
			/// @brief 地址保持时钟周期数。
			///
			/// @return
			///
			int address_hold_clock_cycle_count() const
			{
				base::Fraction value{_address_hold_time / clock_cycle()};
				return static_cast<int>(value.Ceil());
			}

			///
			/// @brief 设置地址保持时钟周期数。
			///
			/// @param value
			///
			void set_address_hold_clock_cycle_count(int value)
			{
				_address_hold_time = value * clock_cycle();
			}

			/* #endregion */

			/* #region 数据建立时间 */

			///
			/// @brief 数据建立时间。
			///
			/// @return
			///
			base::unit::Nanosecond data_setup_time() const
			{
				return _data_setup_time;
			}

			///
			/// @brief 数据建立时间。
			///
			/// @param value
			///
			void set_data_setup_time(base::unit::Nanosecond const &value)
			{
				_data_setup_time = value;
			}

			///
			/// @brief 数据建立时钟周期数。
			///
			/// @return
			///
			int data_setup_clock_cycle_count() const
			{
				base::Fraction value{_data_setup_time / clock_cycle()};
				return static_cast<int>(value.Ceil());
			}

			///
			/// @brief 设置数据建立时钟周期数。
			///
			/// @param value
			///
			void set_data_setup_clock_cycle_count(int value)
			{
				_data_setup_time = value * clock_cycle();
			}

			/* #endregion */

			/* #region 总线周转时间 */

			///
			/// @brief 总线周转时间。
			///
			/// @return
			///
			base::unit::Nanosecond bus_turn_around_time() const
			{
				return _bus_turn_around_time;
			}

			///
			/// @brief 设置总线周转时间。
			///
			/// @param value
			///
			void set_bus_turn_around_time(base::unit::Nanosecond const &value)
			{
				_bus_turn_around_time = value;
			}

			///
			/// @brief 总线周转时钟周期数。
			///
			/// @return
			///
			int bus_turn_around_clock_cycle_count() const
			{
				base::Fraction value{_bus_turn_around_time / clock_cycle()};
				return static_cast<int>(value.Ceil());
			}

			///
			/// @brief 设置总线周转时钟周期数。
			///
			/// @param value
			///
			void set_bus_turn_around_clock_cycle_count(int value)
			{
				_bus_turn_around_time = value * clock_cycle();
			}

			/* #endregion */

			///
			/// @brief 序列化为 json
			///
			/// @return
			///
			virtual base::Json ToJson() const override;
		};

	} // namespace asynchronous_sram
} // namespace base
