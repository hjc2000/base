#include "Fraction.h"

/* #region 四则运算 */

base::Fraction base::Fraction::operator-() const
{
	Fraction ret{-_num, _den};
	return ret.Simplify();
}

base::Fraction base::Fraction::operator+(Fraction const &value) const
{
	// 通分后的分母为本对象的分母和 value 的分母的最小公倍数
	boost::multiprecision::cpp_int scaled_den = boost::multiprecision::lcm(_den, value.Den());

	// 通分后的分子为本对象的分子乘上分母所乘的倍数
	boost::multiprecision::cpp_int scaled_num = _num * (scaled_den / _den);
	boost::multiprecision::cpp_int value_scaled_num = value.Num() * (scaled_den / value.Den());

	Fraction ret{
		scaled_num + value_scaled_num,
		scaled_den,
	};

	return ret.Simplify();
}

base::Fraction base::Fraction::operator-(Fraction const &value) const
{
	Fraction ret = *this + (-value);
	return ret.Simplify();
}

base::Fraction base::Fraction::operator*(Fraction const &value) const
{
	base::Fraction ret;
	ret.SetNum(_num * value.Num());
	ret.SetDen(_den * value.Den());
	return ret.Simplify();
}

base::Fraction base::Fraction::operator/(Fraction const &value) const
{
	Fraction ret{*this * value.Reciprocal()};
	return ret.Simplify();
}

base::Fraction &base::Fraction::operator+=(Fraction const &value)
{
	*this = *this + value;
	return *this;
}

base::Fraction &base::Fraction::operator-=(Fraction const &value)
{
	*this = *this - value;
	return *this;
}

base::Fraction &base::Fraction::operator*=(Fraction const &value)
{
	*this = *this * value;
	return *this;
}

base::Fraction &base::Fraction::operator/=(Fraction const &value)
{
	*this = *this / value;
	return *this;
}

/* #endregion */

std::string base::Fraction::ToString() const
{
	return std::to_string(_num) + " / " + std::to_string(_den);
}

/* #region 比较 */

bool base::Fraction::operator==(Fraction const &another) const
{
	if (Num() == 0 && another.Num() == 0)
	{
		/* 2 个分子都为 0 直接返回相等，这样更加安全，避免分子都为 0
		 * 分母不相等时错误地将两个分数判断为不相等。
		 */
		return true;
	}

	Fraction f1 = Simplify();
	Fraction f2 = another.Simplify();
	return f1.Num() == f2.Num() && f1.Den() == f2.Den();
}

bool base::Fraction::operator>(Fraction const &another) const
{
	// 先化简，避免分母为负数，然后使用交叉乘法比大小。
	Fraction f1 = Simplify();
	Fraction f2 = another.Simplify();
	boost::multiprecision::cpp_int num1{f1.Num()};
	boost::multiprecision::cpp_int den1{f1.Den()};
	boost::multiprecision::cpp_int num2{f2.Num()};
	boost::multiprecision::cpp_int den2{f2.Den()};
	return num1 * den2 > num2 * den1;
}

bool base::Fraction::operator<(Fraction const &another) const
{
	// 先化简，避免分母为负数，然后使用交叉乘法比大小。
	Fraction f1 = Simplify();
	Fraction f2 = another.Simplify();
	boost::multiprecision::cpp_int num1{f1.Num()};
	boost::multiprecision::cpp_int den1{f1.Den()};
	boost::multiprecision::cpp_int num2{f2.Num()};
	boost::multiprecision::cpp_int den2{f2.Den()};
	return num1 * den2 < num2 * den1;
}

bool base::Fraction::operator>=(Fraction const &another) const
{
	if (*this == another)
	{
		return true;
	}

	if (*this > another)
	{
		return true;
	}

	return false;
}

bool base::Fraction::operator<=(Fraction const &another) const
{
	if (*this == another)
	{
		return true;
	}

	if (*this < another)
	{
		return true;
	}

	return false;
}

/* #endregion */

/* #region 全局四则运算符 */

base::Fraction operator+(boost::multiprecision::cpp_int left, base::Fraction const &right)
{
	return base::Fraction{left} + right;
}

base::Fraction operator-(boost::multiprecision::cpp_int left, base::Fraction const &right)
{
	return base::Fraction{left} - right;
}

base::Fraction operator*(boost::multiprecision::cpp_int left, base::Fraction const &right)
{
	return base::Fraction(left) * right;
}

base::Fraction operator/(boost::multiprecision::cpp_int left, base::Fraction const &right)
{
	return base::Fraction{left} / right;
}

/* #endregion */

/* #region 全局计算函数 */

boost::multiprecision::cpp_int std::floor(base::Fraction const &value)
{
	return value.Floor();
}

boost::multiprecision::cpp_int std::ceil(base::Fraction const &value)
{
	return value.Ceil();
}

/* #endregion */

namespace
{
	base::Fraction _pi{
		static_cast<uint64_t>(884279719003555),
		static_cast<uint64_t>(281474976710656),
	};

}

base::Fraction base::constant::PI()
{
	return _pi;
}

std::string std::to_string(boost::multiprecision::cpp_int const &value)
{
	boost::multiprecision::cpp_int temp = value;
	bool is_negative = temp < 0;
	std::string ret;
	if (temp < 0)
	{
		temp = -temp;
	}

	while (temp > 0)
	{
		uint8_t num = static_cast<uint8_t>(temp % 10);
		ret = std::to_string(num) + ret;
		temp /= 10;
	}

	if (is_negative)
	{
		ret = '-' + ret;
	}

	return ret;
}
