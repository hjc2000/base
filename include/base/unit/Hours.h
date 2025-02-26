#pragma once
#include <base/unit/IUnit.h>
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
		explicit Hours(base::Fraction const &value);
		explicit Hours(int64_t value);
		explicit Hours(base::Days const &value);
		explicit Hours(base::Minutes const &value);
		explicit Hours(base::Seconds const &value);
		explicit Hours(base::Nanoseconds const &value);
		explicit Hours(base::Hz const &value);
		explicit Hours(base::MHz const &value);
		explicit Hours(std::chrono::seconds const &value);
		explicit Hours(std::chrono::milliseconds const &value);
		explicit Hours(std::chrono::microseconds const &value);

	public:
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
