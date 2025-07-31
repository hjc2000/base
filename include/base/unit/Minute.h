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
		class Hour;
		class Minute;
		class Nanosecond;

		/// @brief 分钟。
		class Minute :
			public base::unit::IUnit<Minute>
		{
		private:
			base::Fraction _value{};

		public:
			Minute() = default;

			template <typename value_type>
				requires(std::is_integral_v<value_type>)
			explicit Minute(value_type value)
			{
				_value = value;
			}

			explicit Minute(base::Fraction const &value);
			explicit Minute(base::unit::Hour const &value);
			explicit Minute(base::unit::Second const &value);
			explicit Minute(base::unit::Nanosecond const &value);
			explicit Minute(base::unit::Hz const &value);
			explicit Minute(base::unit::MHz const &value);
			explicit Minute(std::chrono::seconds const &value);
			explicit Minute(std::chrono::milliseconds const &value);
			explicit Minute(std::chrono::microseconds const &value);
			explicit Minute(std::chrono::nanoseconds const &value);

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
				base::unit::Second ret{_value * 60};
				return ret;
			}
		};

	} // namespace unit
} // namespace base
