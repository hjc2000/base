#pragma once
#include "base/unit/IUnit.h"
#include <chrono>

namespace base
{
	class Hz;
	class MHz;
	class Hours;
	class Minutes;
	class Seconds;
	class Nanoseconds;

	/// @brief 分钟。
	class Minutes :
		public base::IUnit<Minutes>
	{
	private:
		base::Fraction _value{};

	public:
		Minutes() = default;
		explicit Minutes(base::Fraction const &value);
		explicit Minutes(int64_t value);
		explicit Minutes(base::Hours const &value);
		explicit Minutes(base::Seconds const &value);
		explicit Minutes(base::Nanoseconds const &value);
		explicit Minutes(base::Hz const &value);
		explicit Minutes(base::MHz const &value);
		explicit Minutes(std::chrono::seconds const &value);
		explicit Minutes(std::chrono::milliseconds const &value);
		explicit Minutes(std::chrono::microseconds const &value);

		virtual base::Fraction &Value() override
		{
			return _value;
		}

		/// @brief 单位的字符串。
		/// @return
		virtual std::string UnitString() const override;

		explicit operator std::chrono::seconds() const;
		explicit operator std::chrono::milliseconds() const;
		explicit operator std::chrono::microseconds() const;
	};
} // namespace base
