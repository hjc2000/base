#pragma once
#include "base/int64-unit/Hour.h"
#include "base/int64-unit/IUnit.h"
#include "base/int64-unit/Second.h"
#include <chrono>

namespace base
{
	namespace int64_unit
	{
		class Day :
			public base::int64_unit::IUnit<Day>
		{
		private:
			base::Int64Fraction _value{};

		public:
			Day() = default;

			template <typename value_type>
				requires(std::is_integral_v<value_type>)
			explicit Day(value_type value)
			{
				_value = value;
			}

			explicit Day(base::Int64Fraction const &value)
			{
				_value = value;
			}

			Day(base::int64_unit::Second const &value)
			{
				base::int64_unit::Hour hour{value};
				_value = hour.Value() / 24;
			}

			///
			/// @brief 能转换到 base::int64_unit::Second 的对象都借助 base::int64_unit::Second
			/// 进行构造。
			///
			template <typename T>
				requires(std::is_convertible_v<T, base::int64_unit::Second>)
			Day(T const &value)
				: Day(base::int64_unit::Second{value})
			{
			}

			///
			/// @brief 单位的值。
			///
			/// @return
			///
			virtual base::Int64Fraction &Value() override
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

			explicit operator std::chrono::days() const
			{
				return std::chrono::days{base::int64_unit::Second{*this}};
			}

			explicit operator std::chrono::hours() const
			{
				return std::chrono::hours{base::int64_unit::Second{*this}};
			}

			explicit operator std::chrono::minutes() const
			{
				return std::chrono::minutes{base::int64_unit::Second{*this}};
			}

			explicit operator std::chrono::seconds() const
			{
				return std::chrono::seconds{base::int64_unit::Second{*this}};
			}

			explicit operator std::chrono::milliseconds() const
			{
				return std::chrono::milliseconds{base::int64_unit::Second{*this}};
			}

			explicit operator std::chrono::microseconds() const
			{
				return std::chrono::microseconds{base::int64_unit::Second{*this}};
			}

			explicit operator std::chrono::nanoseconds() const
			{
				return std::chrono::nanoseconds{base::int64_unit::Second{*this}};
			}

			operator base::int64_unit::Second() const
			{
				base::int64_unit::Hour hour{_value * 24};
				return base::int64_unit::Second{hour};
			}
		};

	} // namespace int64_unit
} // namespace base
