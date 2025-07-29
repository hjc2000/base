#pragma once
#include "base/unit/IUnit.h"
#include <chrono>

namespace base
{
	namespace unit
	{
		class Hz;
		class MHz;
		class Hours;
		class Minutes;
		class Seconds;
		class Nanoseconds;

		/// @brief 分钟。
		class Minutes :
			public base::IUnit<Minutes>
		{
		private:
			base::Fraction _value{};

		public:
			Minutes() = default;

			template <typename value_type>
				requires(std::is_integral_v<value_type>)
			explicit Minutes(value_type value)
			{
				_value = value;
			}

			explicit Minutes(base::Fraction const &value);
			explicit Minutes(base::unit::Hours const &value);
			explicit Minutes(base::unit::Seconds const &value);
			explicit Minutes(base::unit::Nanoseconds const &value);
			explicit Minutes(base::unit::Hz const &value);
			explicit Minutes(base::unit::MHz const &value);
			explicit Minutes(std::chrono::seconds const &value);
			explicit Minutes(std::chrono::milliseconds const &value);
			explicit Minutes(std::chrono::microseconds const &value);
			explicit Minutes(std::chrono::nanoseconds const &value);

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
