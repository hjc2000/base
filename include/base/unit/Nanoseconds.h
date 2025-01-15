#pragma once
#include <base/math/Fraction.h>
#include <chrono>

namespace base
{
	class Hz;
	class Seconds;

	/// @brief 纳秒
	class Nanoseconds :
		public base::ICanToString
	{
	private:
		base::Fraction _value{1};

	public:
#pragma region 生命周期
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
#pragma endregion

#pragma region 强制转换

		explicit operator base::Fraction() const
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

		explicit operator int64_t() const
		{
			return static_cast<int64_t>(_value);
		}

		explicit operator double() const
		{
			return static_cast<double>(_value);
		}

		explicit operator std::string() const
		{
			return static_cast<std::string>(_value);
		}

#pragma endregion

#pragma region 四则运算符

		Nanoseconds operator-() const
		{
			return -_value;
		}

		Nanoseconds operator+(Nanoseconds const &value) const
		{
			return _value + static_cast<base::Fraction>(value);
		}

		Nanoseconds operator-(Nanoseconds const &value) const
		{
			return _value - static_cast<base::Fraction>(value);
		}

		Nanoseconds operator*(Nanoseconds const &value) const
		{
			return _value * static_cast<base::Fraction>(value);
		}

		Nanoseconds operator/(Nanoseconds const &value) const
		{
			return _value / static_cast<base::Fraction>(value);
		}

		Nanoseconds &operator+=(Nanoseconds const &value)
		{
			_value += static_cast<base::Fraction>(value);
			return *this;
		}

		Nanoseconds &operator-=(Nanoseconds const &value)
		{
			_value -= static_cast<base::Fraction>(value);
			return *this;
		}

		Nanoseconds &operator*=(Nanoseconds const &value)
		{
			_value *= static_cast<base::Fraction>(value);
			return *this;
		}

		Nanoseconds &operator/=(Nanoseconds const &value)
		{
			_value /= static_cast<base::Fraction>(value);
			return *this;
		}

#pragma endregion

#pragma region 比较运算符

		bool operator==(Nanoseconds const &value) const
		{
			return _value == value._value;
		}

		bool operator<(Nanoseconds const &value) const
		{
			return _value < value._value;
		}

		bool operator>(Nanoseconds const &value) const
		{
			return _value > value._value;
		}

		bool operator<=(Nanoseconds const &value) const
		{
			return _value <= value._value;
		}

		bool operator>=(Nanoseconds const &value) const
		{
			return _value >= value._value;
		}

#pragma endregion

		/// @brief 转化为字符串
		/// @return
		std::string ToString() const override
		{
			return _value.ToString();
		}
	};
} // namespace base
