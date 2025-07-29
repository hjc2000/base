#pragma once
#include "base/unit/IUnit.h"
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

		/// @brief 秒
		class Second :
			public base::unit::IUnit<Second>
		{
		private:
			base::Fraction _value{};

		public:
			Second() = default;

			template <typename value_type>
				requires(std::is_integral_v<value_type>)
			explicit Second(value_type value)
			{
				_value = value;
			}

			explicit Second(base::Fraction const &value);
			explicit Second(base::unit::Hour const &value);
			explicit Second(base::unit::Minute const &value);
			explicit Second(base::unit::Nanosecond const &value);
			explicit Second(base::unit::Hz const &value);
			explicit Second(base::unit::MHz const &value);
			explicit Second(std::chrono::seconds const &value);
			explicit Second(std::chrono::milliseconds const &value);
			explicit Second(std::chrono::microseconds const &value);
			explicit Second(std::chrono::nanoseconds const &value);

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
