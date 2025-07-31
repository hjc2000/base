#pragma once
#include "base/unit/IUnit.h"
#include "base/unit/Second.h"

namespace base
{
	namespace unit
	{
		class Second;
		class Nanosecond;
		class MHz;

		/// @brief 频率单位：Hz.
		class Hz :
			public base::unit::IUnit<Hz>
		{
		private:
			base::Fraction _value{};

		public:
			Hz() = default;

			template <typename value_type>
				requires(std::is_integral_v<value_type>)
			explicit Hz(value_type value)
			{
				_value = value;
			}

			explicit Hz(base::Fraction const &value)
			{
				_value = value;
			}

			explicit Hz(base::unit::Second const &value)
			{
				_value = static_cast<base::Fraction>(value).Reciprocal();
			}

			explicit Hz(base::unit::MHz const &value);

			explicit Hz(base::unit::Nanosecond const &value);

			///
			/// @brief 单位的值。
			///
			/// @return base::Fraction&
			///
			virtual base::Fraction &Value() override;

			///
			/// @brief 单位的字符串。
			///
			/// @return std::string
			///
			virtual std::string UnitString() const override;
		};

	} // namespace unit
} // namespace base
