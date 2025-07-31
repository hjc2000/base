#pragma once
#include "base/unit/IUnit.h"
#include "base/unit/Second.h"
#include <chrono>

namespace base
{
	namespace unit
	{
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

			explicit Hour(base::Fraction const &value)
			{
				_value = value;
			}

			Hour(base::unit::Second const &value)
			{
				_value = value.Value() / 60 / 60;
			}

			///
			/// @brief 能转换到 base::unit::Second 的对象都借助 base::unit::Second
			/// 进行构造。
			///
			template <typename T>
				requires(std::is_convertible_v<T, base::unit::Second>)
			Hour(T const &value)
				: Hour(base::unit::Second{value})
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
				return "h";
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
				base::unit::Second ret{_value * 60 * 60};
				return ret;
			}
		};

	} // namespace unit
} // namespace base
