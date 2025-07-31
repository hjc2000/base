#pragma once
#include "base/unit/IUnit.h"
#include "base/unit/Second.h"
#include <chrono>

namespace base
{
	namespace unit
	{
		class Hz;
		class MHz;
		class Day;
		class Minute;
		class Nanosecond;

		class Hour :
			public base::unit::IUnit<Hour>
		{
		private:
			base::Fraction _value{};

		public:
			Hour() = default;

			template <typename value_type>
				requires(std::is_integral_v<value_type>)
			explicit Hour(value_type value)
			{
				_value = value;
			}

			explicit Hour(base::Fraction const &value);
			explicit Hour(base::unit::Day const &value);
			explicit Hour(base::unit::Minute const &value);

			explicit Hour(base::unit::Second const &value)
			{
				_value = value.Value() / 60 / 60;
			}

			explicit Hour(base::unit::Nanosecond const &value);
			explicit Hour(base::unit::Hz const &value);
			explicit Hour(base::unit::MHz const &value);
			explicit Hour(std::chrono::seconds const &value);
			explicit Hour(std::chrono::milliseconds const &value);
			explicit Hour(std::chrono::microseconds const &value);
			explicit Hour(std::chrono::nanoseconds const &value);

			///
			/// @brief 单位的值。
			///
			/// @return
			///
			virtual base::Fraction &Value() override;

			///
			/// @brief 单位的字符串。
			///
			/// @return
			///
			virtual std::string UnitString() const override;

			explicit operator std::chrono::days() const;
			explicit operator std::chrono::hours() const;
			explicit operator std::chrono::minutes() const;
			explicit operator std::chrono::seconds() const;
			explicit operator std::chrono::milliseconds() const;
			explicit operator std::chrono::microseconds() const;
			explicit operator std::chrono::nanoseconds() const;

			operator base::unit::Second() const
			{
				base::unit::Second ret{_value * 60 * 60};
				return ret;
			}
		};

	} // namespace unit
} // namespace base
