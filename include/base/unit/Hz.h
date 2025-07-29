#pragma once
#include "base/unit/IUnit.h"

namespace base
{
	namespace unit
	{
		class Seconds;
		class Nanoseconds;
		class MHz;

		/// @brief 频率单位：Hz.
		class Hz :
			public base::IUnit<Hz>
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

			explicit Hz(base::Fraction const &value);
			explicit Hz(base::unit::MHz const &value);
			explicit Hz(base::unit::Seconds const &value);
			explicit Hz(base::unit::Nanoseconds const &value);

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
