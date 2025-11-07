#pragma once
#include "base/int64-unit/bps.h"
#include "base/int64-unit/IUnit.h"

namespace base
{
	namespace int64_unit
	{
		///
		/// @brief 比特率。每秒的比特数。这里是 Mbit / s.
		///
		/// @note 在通信领域，1 Mbit = 1000 * 1000 bit.
		///
		class Mbps :
			public base::int64_unit::IUnit<Mbps>
		{
		private:
			base::Int64Fraction _value{};

		public:
			Mbps() = default;

			template <typename value_type>
				requires(std::is_integral_v<value_type>)
			explicit Mbps(value_type value)
			{
				_value = value;
			}

			explicit Mbps(base::Int64Fraction const &o)
			{
				_value = o;
			}

			Mbps(base::int64_unit::bps const &o)
			{
				_value = static_cast<base::Int64Fraction>(o) / 1000 / 1000;
			}

			///
			/// @brief 能转换为 base::int64_unit::bps 的对象都利用 base::int64_unit::bps 进行初始化。
			///
			///
			template <typename T>
				requires(std::is_convertible_v<T, base::int64_unit::bps>)
			Mbps(T const &value)
				: Mbps(base::int64_unit::bps{value})
			{
			}

			using base::int64_unit::IUnit<Mbps>::Value;

			virtual base::Int64Fraction &Value() override
			{
				return _value;
			}

			/// @brief 单位的字符串。
			/// @return
			virtual std::string UnitString() const override
			{
				return "Mbps";
			}

			operator base::int64_unit::bps() const
			{
				base::int64_unit::bps ret{_value * 1000 * 1000};
				return ret;
			}
		};

	} // namespace int64_unit
} // namespace base
