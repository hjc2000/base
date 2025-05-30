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

	class Days :
		public base::IUnit<Days>
	{
	private:
		base::Fraction _value{};

	public:
		Days() = default;

		template <typename value_type>
			requires(std::is_integral_v<value_type>)
		explicit Days(value_type value)
		{
			_value = value;
		}

		explicit Days(base::Fraction const &value);
		explicit Days(base::Hours const &value);
		explicit Days(base::Minutes const &value);
		explicit Days(base::Seconds const &value);
		explicit Days(base::Nanoseconds const &value);
		explicit Days(base::Hz const &value);
		explicit Days(base::MHz const &value);
		explicit Days(std::chrono::seconds const &value);
		explicit Days(std::chrono::milliseconds const &value);
		explicit Days(std::chrono::microseconds const &value);
		explicit Days(std::chrono::nanoseconds const &value);

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
