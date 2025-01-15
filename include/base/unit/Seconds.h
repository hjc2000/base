#pragma once
#include <base/math/Fraction.h>
#include <chrono>

namespace base
{
	class Hz;
	class Nanoseconds;

	/// @brief 秒
	class Seconds :
		public base::ICanToString
	{
	private:
		base::Fraction _value{1};

	public:
#pragma region 生命周期
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
#pragma endregion

#pragma region 强制转换

		explicit operator base::Fraction() const
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

		Seconds operator-() const
		{
			return -_value;
		}

		Seconds operator+(Seconds const &value) const;
		Seconds operator-(Seconds const &value) const;
		Seconds operator*(Seconds const &value) const;
		Seconds operator/(Seconds const &value) const;

		Seconds &operator+=(Seconds const &value);
		Seconds &operator-=(Seconds const &value);
		Seconds &operator*=(Seconds const &value);
		Seconds &operator/=(Seconds const &value);
#pragma endregion

#pragma region 比较运算符

		bool operator==(Seconds const &value) const
		{
			return _value == value._value;
		}

		bool operator<(Seconds const &value) const
		{
			return _value < value._value;
		}

		bool operator>(Seconds const &value) const
		{
			return _value > value._value;
		}

		bool operator<=(Seconds const &value) const
		{
			return _value <= value._value;
		}

		bool operator>=(Seconds const &value) const
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

std::ostream &operator<<(std::ostream &ostream, base::Seconds const &right);
base::Seconds operator+(int64_t left, base::Seconds const &right);
base::Seconds operator-(int64_t left, base::Seconds const &right);
base::Seconds operator*(int64_t left, base::Seconds const &right);
base::Seconds operator/(int64_t left, base::Seconds const &right);
