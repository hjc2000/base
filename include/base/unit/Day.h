#pragma once
#include "base/unit/IUnit.h"
#include <chrono>

namespace base
{
	class Hz;
	class MHz;
	class Day;
	class Hours;
	class Minutes;
	class Seconds;
	class Nanoseconds;

	class Day :
		public base::IUnit<Day>
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

		explicit Day(base::Fraction const &value);
		explicit Day(base::Hours const &value);
		explicit Day(base::Minutes const &value);
		explicit Day(base::Seconds const &value);
		explicit Day(base::Nanoseconds const &value);
		explicit Day(base::Hz const &value);
		explicit Day(base::MHz const &value);
		explicit Day(std::chrono::seconds const &value);
		explicit Day(std::chrono::milliseconds const &value);
		explicit Day(std::chrono::microseconds const &value);
		explicit Day(std::chrono::nanoseconds const &value);

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
} // namespace base
