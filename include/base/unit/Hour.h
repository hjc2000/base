#pragma once
#include "base/unit/IUnit.h"
#include <chrono>

namespace base
{
	namespace unit
	{
		class Hz;
		class MHz;
		class Day;
		class Hour;
		class Minute;
		class Seconds;
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
			explicit Hour(base::unit::Seconds const &value);
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
			/// @return base::Fraction&
			///
			virtual base::Fraction &Value() override;

			///
			/// @brief 单位的字符串。
			///
			/// @return std::string
			///
			virtual std::string UnitString() const override;

			explicit operator std::chrono::days() const;
			explicit operator std::chrono::hours() const;
			explicit operator std::chrono::minutes() const;
			explicit operator std::chrono::seconds() const;
			explicit operator std::chrono::milliseconds() const;
			explicit operator std::chrono::microseconds() const;
			explicit operator std::chrono::nanoseconds() const;
		};

	} // namespace unit
} // namespace base
