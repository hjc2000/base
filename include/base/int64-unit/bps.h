#pragma once
#include "base/int64-unit/IUnit.h"

namespace base
{
	namespace int64_unit
	{
		///
		/// @brief 比特率。每秒的比特数。这里是 bit / s.
		///
		///
		class bps :
			public base::int64_unit::IUnit<bps>
		{
		private:
			base::Int64Fraction _value{};

		public:
			bps() = default;

			template <typename value_type>
				requires(std::is_integral_v<value_type>)
			explicit bps(value_type value)
			{
				_value = value;
			}

			explicit bps(base::Int64Fraction const &o)
			{
				_value = o;
			}

			using base::int64_unit::IUnit<bps>::Value;

			///
			/// @brief 单位的值。
			///
			/// @return
			///
			virtual base::Int64Fraction &Value() override
			{
				return _value;
			}

			///
			/// @brief 单位的字符串。
			///
			/// @return
			///
			virtual std::string UnitString() const override
			{
				return "bps";
			}
		};

	} // namespace int64_unit
} // namespace base
