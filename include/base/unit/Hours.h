#pragma once
#include "base/unit/IUnit.h"
#include <chrono>

namespace base
{
	class Hz;
	class MHz;
	class Days;
	class Hours;
	class Minutes;
	class Seconds;
	class Nanoseconds;

	class Hours :
		public base::IUnit<Hours>
	{
	private:
		base::Fraction _value{};

	public:
		Hours() = default;

		template <typename value_type>
			requires(std::is_integral_v<value_type>)
		explicit Hours(value_type value)
		{
			_value = value;
		}

		explicit Hours(base::Fraction const &value);
		explicit Hours(base::Days const &value);
		explicit Hours(base::Minutes const &value);
		explicit Hours(base::Seconds const &value);
		explicit Hours(base::Nanoseconds const &value);
		explicit Hours(base::Hz const &value);
		explicit Hours(base::MHz const &value);
		explicit Hours(std::chrono::seconds const &value);
		explicit Hours(std::chrono::milliseconds const &value);
		explicit Hours(std::chrono::microseconds const &value);
		explicit Hours(std::chrono::nanoseconds const &value);

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
