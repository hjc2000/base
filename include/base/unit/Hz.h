#pragma once
#include "base/unit/IUnit.h"
#include "base/unit/Second.h"

namespace base
{
	namespace unit
	{
		class Second;
		class Nanosecond;

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

			Hz(base::unit::Second const &value)
			{
				_value = static_cast<base::Fraction>(value).Reciprocal();
			}

			template <typename T>
				requires(std::is_convertible_v<T, base::unit::Second>)
			Hz(T const &value)
				: Hz(base::unit::Second{value})
			{
			}

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
				return "Hz";
			}

			operator base::unit::Second() const
			{
				base::unit::Second ret{_value.Reciprocal()};
				return ret;
			}
		};

	} // namespace unit
} // namespace base
