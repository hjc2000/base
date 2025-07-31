#pragma once
#include "base/unit/Hour.h"
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
		class Hour;
		class Minute;
		class Nanosecond;

		class Day :
			public base::unit::IUnit<Day>
		{
		private:
			base::Fraction _value{};

		public:
			Day() = default;

			template <typename value_type>
				requires(std::is_integral_v<value_type>)
			explicit Day(value_type value)
			{
				_value = value;
			}

			explicit Day(base::Fraction const &value)
			{
				_value = value;
			}

			Day(base::unit::Second const &value)
			{
				base::unit::Hour hour{value};
				_value = hour.Value() / 24;
			}

			///
			/// @brief 能转换到 base::unit::Second 的对象都借助 base::unit::Second
			/// 进行构造。
			///
			template <typename T>
				requires(std::is_convertible_v<T, base::unit::Second>)
			Day(T const &value)
				: Day(base::unit::Second{value})
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
				return "d";
			}

			explicit operator std::chrono::days() const;
			explicit operator std::chrono::hours() const;
			explicit operator std::chrono::minutes() const;
			explicit operator std::chrono::seconds() const;
			explicit operator std::chrono::milliseconds() const;
			explicit operator std::chrono::microseconds() const;
			explicit operator std::chrono::nanoseconds() const;

			operator base::unit::Second() const
			{
				base::unit::Hour hour{_value * 24};
				return base::unit::Second{hour};
			}
		};

	} // namespace unit
} // namespace base
