#pragma once
#include "base/math/Fraction.h"
#include "base/unit/IUnit.h"
#include "base/unit/Second.h"
#include <chrono>

namespace base
{
	namespace unit
	{
		class Hz;
		class MHz;
		class Hour;
		class Minute;
		class Second;
		class Nanosecond;

		///
		/// @brief 纳秒
		///
		///
		class Nanosecond :
			public base::unit::IUnit<Nanosecond>
		{
		private:
			base::Fraction _value{};

		public:
			Nanosecond() = default;

			template <typename value_type>
				requires(std::is_integral_v<value_type>)
			explicit Nanosecond(value_type value)
			{
				_value = value;
			}

			explicit Nanosecond(base::Fraction const &value);
			explicit Nanosecond(base::unit::Hour const &value);
			explicit Nanosecond(base::unit::Minute const &value);
			explicit Nanosecond(base::unit::Second const &value);
			explicit Nanosecond(base::unit::Hz const &value);
			explicit Nanosecond(base::unit::MHz const &value);
			explicit Nanosecond(std::chrono::seconds const &value);
			explicit Nanosecond(std::chrono::milliseconds const &value);
			explicit Nanosecond(std::chrono::microseconds const &value);
			explicit Nanosecond(std::chrono::nanoseconds const &value);

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

			operator base::unit::Second() const
			{
				base::unit::Second ret{_value / 1000 / 1000 / 1000};
				return ret;
			}
		};

	} // namespace unit
} // namespace base
