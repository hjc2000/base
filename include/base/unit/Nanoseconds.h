#pragma once
#include <base/math/Fraction.h>
#include <chrono>

namespace base
{
	class Hz;

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
		Nanoseconds(base::Hz const &value);
		Nanoseconds(std::chrono::seconds const &value);
		Nanoseconds(std::chrono::milliseconds const &value);
		Nanoseconds(std::chrono::microseconds const &value);

		Nanoseconds &operator=(Nanoseconds const &o);
#pragma endregion

#pragma region 强制转换
		explicit operator base::Fraction() const;
		explicit operator std::chrono::seconds() const;
		explicit operator std::chrono::milliseconds() const;
		explicit operator std::chrono::microseconds() const;
		explicit operator int64_t() const;
		explicit operator double() const;
		explicit operator std::string() const;
#pragma endregion

#pragma region 四则运算符
		Nanoseconds operator-() const;
		Nanoseconds operator+(Nanoseconds const &value) const;
		Nanoseconds operator-(Nanoseconds const &value) const;
		Nanoseconds operator*(Nanoseconds const &value) const;
		Nanoseconds operator/(Nanoseconds const &value) const;

		Nanoseconds &operator+=(Nanoseconds const &value);
		Nanoseconds &operator-=(Nanoseconds const &value);
		Nanoseconds &operator*=(Nanoseconds const &value);
		Nanoseconds &operator/=(Nanoseconds const &value);
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
