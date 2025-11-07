#pragma once
#include "base/math/Int64Fraction.h"
#include "IUnit.h"

namespace base
{
	namespace int64_unit
	{
		///
		/// @brief 电压单位：伏特。
		///
		///
		class V :
			public base::int64_unit::IUnit<V>
		{
		private:
			base::Int64Fraction _value;

		public:
			V() = default;

			template <typename value_type>
				requires(std::is_integral_v<value_type>)
			explicit V(value_type value)
			{
				_value = value;
			}

			explicit V(base::Int64Fraction const &value)
			{
				_value = value;
			}

			using base::int64_unit::IUnit<V>::Value;

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
				return "V";
			}
		};

	} // namespace int64_unit
} // namespace base
