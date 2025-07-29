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

		/// @brief 秒
		class Seconds :
			public base::IUnit<Seconds>
		{
		private:
			base::Fraction _value{};

		public:
			Seconds() = default;

			template <typename value_type>
				requires(std::is_integral_v<value_type>)
			explicit Seconds(value_type value)
			{
				_value = value;
			}

			explicit Seconds(base::Fraction const &value);
			explicit Seconds(base::unit::Hours const &value);
			explicit Seconds(base::unit::Minutes const &value);
			explicit Seconds(base::unit::Nanoseconds const &value);
			explicit Seconds(base::unit::Hz const &value);
			explicit Seconds(base::unit::MHz const &value);
			explicit Seconds(std::chrono::seconds const &value);
			explicit Seconds(std::chrono::milliseconds const &value);
			explicit Seconds(std::chrono::microseconds const &value);
			explicit Seconds(std::chrono::nanoseconds const &value);

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
