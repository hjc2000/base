#pragma once
#include "base/math/Fraction.h"
#include "IUnit.h"

namespace base
{
	namespace unit
	{
		///
		/// @brief 电压单位：伏特。
		///
		///
		class V :
			public base::unit::IUnit<V>
		{
		private:
			base::Fraction _value;

		public:
			V() = default;

			template <typename value_type>
				requires(std::is_integral_v<value_type>)
			explicit V(value_type value)
			{
				_value = value;
			}

			explicit V(base::Fraction const &value)
			{
				_value = value;
			}

			using base::unit::IUnit<V>::Value;

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
				return "V";
			}
		};

	} // namespace unit
} // namespace base
