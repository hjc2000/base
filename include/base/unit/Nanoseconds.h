#pragma once
#include <base/unit/IUnit.h>
#include <chrono>

namespace base
{
	class Hz;
	class Seconds;

	/// @brief 纳秒
	class Nanoseconds :
		public base::IUnit<Nanoseconds>
	{
	private:
		base::Fraction _value{1};

	public:
		Nanoseconds() = default;
		Nanoseconds(Nanoseconds const &o);
		Nanoseconds(base::Fraction const &value);
		Nanoseconds(int64_t value);
		Nanoseconds(base::Seconds const &value);
		Nanoseconds(base::Hz const &value);
		Nanoseconds(std::chrono::seconds const &value);
		Nanoseconds(std::chrono::milliseconds const &value);
		Nanoseconds(std::chrono::microseconds const &value);
		Nanoseconds &operator=(Nanoseconds const &o);

		virtual base::Fraction &Value() override
		{
			return _value;
		}

		explicit operator std::chrono::seconds() const
		{
			return std::chrono::seconds{static_cast<int64_t>(_value / 1000 / 1000 / 1000)};
		}

		explicit operator std::chrono::milliseconds() const
		{
			return std::chrono::milliseconds{static_cast<int64_t>(_value / 1000 / 1000)};
		}

		explicit operator std::chrono::microseconds() const
		{
			return std::chrono::microseconds{static_cast<int64_t>(_value / 1000)};
		}
	};
} // namespace base
