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
		explicit Days(base::Fraction const &value);
		explicit Days(int64_t value);
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

		virtual base::Fraction &Value() override
		{
			return _value;
		}

		/// @brief 单位的字符串。
		/// @return
		virtual std::string UnitString() const override
		{
			return "d";
		}

		explicit operator std::chrono::seconds() const;
		explicit operator std::chrono::milliseconds() const;
		explicit operator std::chrono::microseconds() const;
	};
} // namespace base
