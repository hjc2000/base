#pragma once
#include "base/unit/IUnit.h"
#include <chrono>

namespace base
{
	namespace unit
	{
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

			explicit Second(base::Fraction const &value)
			{
				_value = value;
			}

			Second(std::chrono::seconds const &value)
			{
				_value = base::Fraction{value.count()};
			}

			Second(std::chrono::milliseconds const &value)
			{
				_value = base::Fraction{value.count()} / 1000;
			}

			Second(std::chrono::microseconds const &value)
			{
				_value = base::Fraction{value.count()} / 1000 / 1000;
			}

			Second(std::chrono::nanoseconds const &value)
			{
				_value = base::Fraction{value.count()} / 1000 / 1000 / 1000;
			}

			using base::unit::IUnit<Second>::Value;

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
				return "s";
			}

			explicit operator std::chrono::days() const
			{
				return std::chrono::days{static_cast<int64_t>(_value / 60 / 60 / 24)};
			}

			explicit operator std::chrono::hours() const
			{
				return std::chrono::hours{static_cast<int64_t>(_value / 60 / 60)};
			}

			explicit operator std::chrono::minutes() const
			{
				return std::chrono::minutes{static_cast<int64_t>(_value / 60)};
			}

			explicit operator std::chrono::seconds() const
			{
				return std::chrono::seconds{static_cast<int64_t>(_value)};
			}

			explicit operator std::chrono::milliseconds() const
			{
				return std::chrono::milliseconds{static_cast<int64_t>(_value * 1000)};
			}

			explicit operator std::chrono::microseconds() const
			{
				return std::chrono::microseconds{static_cast<int64_t>(_value * 1000 * 1000)};
			}

			explicit operator std::chrono::nanoseconds() const
			{
				return std::chrono::nanoseconds{static_cast<int64_t>(_value * 1000 * 1000 * 1000)};
			}
		};

	} // namespace unit
} // namespace base
