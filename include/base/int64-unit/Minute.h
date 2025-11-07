#pragma once
#include "base/int64-unit/IUnit.h"
#include "base/int64-unit/Second.h"
#include <chrono>

namespace base
{
	namespace int64_unit
	{
		/// @brief 分钟。
		class Minute :
			public base::int64_unit::IUnit<Minute>
		{
		private:
			base::Int64Fraction _value{};

		public:
			Minute() = default;

			template <typename value_type>
				requires(std::is_integral_v<value_type>)
			explicit Minute(value_type value)
			{
				_value = value;
			}

			explicit Minute(base::Int64Fraction const &value)
			{
				_value = value;
			}

			Minute(base::int64_unit::Second const &value)
			{
				_value = static_cast<base::Int64Fraction>(value) / 60;
			}

			///
			/// @brief 能转换到 base::int64_unit::Second 的对象都借助 base::int64_unit::Second
			/// 进行构造。
			///
			template <typename T>
				requires(std::is_convertible_v<T, base::int64_unit::Second>)
			Minute(T const &value)
				: Minute(base::int64_unit::Second{value})
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
				return "m";
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
				base::int64_unit::Second ret{_value * 60};
				return ret;
			}
		};

	} // namespace int64_unit
} // namespace base
