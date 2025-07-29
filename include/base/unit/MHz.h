#pragma once
#include "base/unit/IUnit.h"
#include <type_traits>

namespace base
{
	namespace unit
	{
		class Second;
		class Nanosecond;
		class Hz;

		///
		/// @brief 频率单位：MHz.
		///
		///
		class MHz :
			public base::unit::IUnit<MHz>
		{
		private:
			base::Fraction _value{};

		public:
			MHz() = default;

			template <typename value_type>
				requires(std::is_integral_v<value_type>)
			explicit MHz(value_type value)
			{
				_value = value;
			}

			explicit MHz(base::Fraction const &value);
			explicit MHz(base::unit::Hz const &value);
			explicit MHz(base::unit::Second const &value);
			explicit MHz(base::unit::Nanosecond const &value);

			using base::unit::IUnit<MHz>::Value;

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
