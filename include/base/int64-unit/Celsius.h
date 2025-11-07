#pragma once
#include "base/int64-unit/IUnit.h"
#include "base/math/Int64Fraction.h"

namespace base
{
	namespace int64_unit
	{
		///
		/// @brief 温度单位。摄氏度 ℃.
		///
		///
		class Celsius :
			public base::int64_unit::IUnit<Celsius>
		{
		private:
			base::Int64Fraction _value;

		public:
			Celsius() = default;

			template <typename value_type>
				requires(std::is_integral_v<value_type>)
			explicit Celsius(value_type value)
			{
				_value = value;
			}

			explicit Celsius(base::Int64Fraction const &value)
			{
				_value = value;
			}

			using base::int64_unit::IUnit<Celsius>::Value;

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
				return "℃";
			}
		};

	} // namespace int64_unit
} // namespace base
