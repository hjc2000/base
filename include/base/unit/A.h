#pragma once
#include "base/math/Fraction.h"
#include "IUnit.h"

namespace base
{
	namespace unit
	{
		///
		/// @brief 电流单位：安培。
		///
		///
		class A :
			public base::unit::IUnit<A>
		{
		private:
			base::Fraction _value;

		public:
			A() = default;

			template <typename value_type>
				requires(std::is_integral_v<value_type>)
			explicit A(value_type value)
			{
				_value = value;
			}

			explicit A(base::Fraction const &value)
			{
				_value = value;
			}

			using base::unit::IUnit<A>::Value;

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
				return "A";
			}
		};

	} // namespace unit
} // namespace base
