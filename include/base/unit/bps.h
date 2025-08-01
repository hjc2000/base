#pragma once
#include "base/unit/IUnit.h"

namespace base
{
	namespace unit
	{
		///
		/// @brief 比特率。每秒的比特数。这里是 bit / s.
		///
		///
		class bps :
			public base::unit::IUnit<bps>
		{
		private:
			base::Fraction _value{};

		public:
			bps() = default;

			template <typename value_type>
				requires(std::is_integral_v<value_type>)
			explicit bps(value_type value)
			{
				_value = value;
			}

			explicit bps(base::Fraction const &o)
			{
				_value = o;
			}

			using base::unit::IUnit<bps>::Value;

			///
			/// @brief 单位的值。
			///
			/// @return
			///
			virtual base::Fraction &Value() override
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

	} // namespace unit
} // namespace base
