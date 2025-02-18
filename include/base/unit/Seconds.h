#pragma once
#include <base/unit/IUnit.h>
#include <chrono>

namespace base
{
	class Hz;
	class MHz;
	class Hours;
	class Minutes;
	class Seconds;
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
		explicit Seconds(base::Fraction const &value);
		explicit Seconds(int64_t value);
		explicit Seconds(base::Hours const &value);
		explicit Seconds(base::Minutes const &value);
		explicit Seconds(base::Nanoseconds const &value);
		explicit Seconds(base::Hz const &value);
		explicit Seconds(base::MHz const &value);
		explicit Seconds(std::chrono::seconds const &value);
		explicit Seconds(std::chrono::milliseconds const &value);
		explicit Seconds(std::chrono::microseconds const &value);
		Seconds &operator=(Seconds const &o);

		virtual base::Fraction &Value() override
		{
			return _value;
		}

		/// @brief 单位的字符串。
		/// @return
		virtual std::string UnitString() const override;

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
