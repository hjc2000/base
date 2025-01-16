#pragma once
#include <base/unit/IUnit.h>
#include <chrono>

namespace base
{
	class Hz;
	class Nanoseconds;

	/// @brief 秒
	class Seconds :
		public base::IUnit<Seconds>
	{
	private:
		base::Fraction _value{1};

	public:
		Seconds() = default;
		Seconds(Seconds const &o);
		Seconds(base::Fraction const &value);
		Seconds(int64_t value);
		Seconds(base::Nanoseconds const &value);
		Seconds(base::Hz const &value);
		Seconds(std::chrono::seconds const &value);
		Seconds(std::chrono::milliseconds const &value);
		Seconds(std::chrono::microseconds const &value);
		Seconds &operator=(Seconds const &o);

		virtual base::Fraction &Value() override
		{
			return _value;
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
	};
} // namespace base
