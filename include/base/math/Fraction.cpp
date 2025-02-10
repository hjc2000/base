#include "Fraction.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <numeric>
#include <stdexcept>

#pragma region 生命周期

base::Fraction::Fraction(int64_t num)
{
	SetNum(num);
	SetDen(1);
}

base::Fraction::Fraction(int64_t num, int64_t den)
{
	SetNum(num);
	SetDen(den);
}

base::Fraction::Fraction(Fraction const &o)
{
	SetNum(o.Num());
	SetDen(o.Den());
}

base::Fraction &base::Fraction::operator=(Fraction const &o)
{
	SetNum(o.Num());
	SetDen(o.Den());
	return *this;
}

#pragma endregion

int64_t base::Fraction::Num() const
{
	return _num;
}

void base::Fraction::SetNum(int64_t value)
{
	_num = value;
}

int64_t base::Fraction::Den() const
{
	return _den;
}

void base::Fraction::SetDen(int64_t value)
{
	if (value == 0)
	{
		throw std::invalid_argument{"分母不能为 0."};
	}

	_den = value;
}

base::Fraction base::Fraction::Simplify() const
{
	if (_den == 0)
	{
		throw std::invalid_argument{"分母不能为 0."};
	}

	// 分子分母同时除以最大公约数
	int64_t gcd_value = std::gcd(_num, _den);
	int64_t scaled_num = _num / gcd_value;
	int64_t scaled_den = _den / gcd_value;

	if (scaled_den < 0)
	{
		// 如果分母小于 0，分子分母同时取相反数
		scaled_num = -scaled_num;
		scaled_den = -scaled_den;
	}

	Fraction ret{scaled_num, scaled_den};
	return ret;
}

base::Fraction base::Fraction::Reciprocal() const
{
	base::Fraction ret{_den, _num};
	return ret.Simplify();
}

int64_t base::Fraction::Floor() const
{
	int64_t ret = Div();
	if (*this < 0)
	{
		if (Mod())
		{
			ret -= 1;
		}
	}
	else
	{
		/* 因为 C++ 除法近 0 截断，所以如果 Div >0 ，本来就是向下取整了，
		 * 不用再额外的操作了。
		 *
		 * Div = 0 就更不用说了，也不用什么额外的操作，直接返回 0 就完事了。
		 */
	}

	return ret;
}

int64_t base::Fraction::Ceil() const
{
	int64_t ret = Div();
	if (*this > 0)
	{
		if (Mod())
		{
			ret += 1;
		}
	}
	else
	{
	}

	return ret;
}

base::Fraction base::Fraction::operator-() const
{
	Fraction ret{-_num, _den};
	return ret.Simplify();
}

base::Fraction base::Fraction::operator+(Fraction const &value) const
{
	// 通分后的分母为本对象的分母和 value 的分母的最小公倍数
	int64_t scaled_den = std::lcm(_den, value.Den());

	// 通分后的分子为本对象的分子乘上分母所乘的倍数
	int64_t scaled_num = _num * (scaled_den / _den);
	int64_t value_scaled_num = value.Num() * (scaled_den / value.Den());

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

#pragma region 强制转换

int64_t base::Fraction::Div() const
{
	return _num / _den;
}

int64_t base::Fraction::Mod() const
{
	return _num % _den;
}

double base::Fraction::ToDouble() const
{
	return static_cast<double>(_num) / _den;
}

std::string base::Fraction::ToString() const
{
	return std::to_string(_num) + " / " + std::to_string(_den);
}

base::Fraction::operator int64_t() const
{
	return Div();
}

base::Fraction::operator double() const
{
	return ToDouble();
}

#pragma endregion

#pragma region 比较

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

#pragma endregion

#pragma region 全局重载运算符

std::ostream &operator<<(std::ostream &ostream, base::Fraction const &right)
{
	ostream << right.ToString();
	return ostream;
}

base::Fraction operator+(int64_t left, base::Fraction const &right)
{
	return base::Fraction{left} + right;
}

base::Fraction operator-(int64_t left, base::Fraction const &right)
{
	return base::Fraction{left} - right;
}

base::Fraction operator*(int64_t left, base::Fraction const &right)
{
	return base::Fraction(left) * right;
}

base::Fraction operator/(int64_t left, base::Fraction const &right)
{
	return base::Fraction{left} / right;
}

#pragma endregion

int64_t std::floor(base::Fraction const &value)
{
	return value.Floor();
}

int64_t std::ceil(base::Fraction const &value)
{
	return value.Ceil();
}
