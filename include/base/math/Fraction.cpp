#include "Fraction.h"
#include "base/math/Pow.h"
#include <cstdint>
#include <stdexcept>

/* #region 构造函数 */

base::Fraction::Fraction(boost::multiprecision::cpp_int num)
{
	SetNum(num);
	SetDen(1);
}

base::Fraction::Fraction(boost::multiprecision::cpp_int num, boost::multiprecision::cpp_int den)
{
	SetNum(num);
	SetDen(den);
}

base::Fraction::Fraction(base::Double const &value)
{
	double db = value.Value();
	int loop_times = 0;
	int64_t factor = base::IntPow(2, 63);
	while (db != 0)
	{
		int64_t int_part = static_cast<int64_t>(db);
		base::Fraction temp{int_part, base::BigIntPow(factor, loop_times)};
		(*this) += temp;
		db -= int_part;
		db *= factor;
		++loop_times;
	}
}

/* #endregion */

/* #region 分子分母 */

boost::multiprecision::cpp_int base::Fraction::Num() const
{
	return _num;
}

void base::Fraction::SetNum(boost::multiprecision::cpp_int value)
{
	_num = value;
}

boost::multiprecision::cpp_int base::Fraction::Den() const
{
	return _den;
}

void base::Fraction::SetDen(boost::multiprecision::cpp_int value)
{
	if (value == 0)
	{
		throw std::invalid_argument{"分母不能为 0."};
	}

	_den = value;
}

/* #endregion */

/* #region 计算函数 */

base::Fraction base::Fraction::Simplify() const
{
	if (_den == 0)
	{
		throw std::invalid_argument{"分母不能为 0."};
	}

	// 分子分母同时除以最大公约数
	boost::multiprecision::cpp_int gcd_value = boost::multiprecision::gcd(_num, _den);
	boost::multiprecision::cpp_int scaled_num = _num / gcd_value;
	boost::multiprecision::cpp_int scaled_den = _den / gcd_value;

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

boost::multiprecision::cpp_int base::Fraction::Floor() const
{
	boost::multiprecision::cpp_int ret = Div();
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

boost::multiprecision::cpp_int base::Fraction::Ceil() const
{
	boost::multiprecision::cpp_int ret = Div();
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

boost::multiprecision::cpp_int base::Fraction::Div() const
{
	return _num / _den;
}

boost::multiprecision::cpp_int base::Fraction::Mod() const
{
	return _num % _den;
}

/* #endregion */

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

/* #region 强制转换运算符 */

base::Fraction::operator boost::multiprecision::cpp_int() const
{
	return Div();
}

base::Fraction::operator int64_t() const
{
	return static_cast<int64_t>(Div());
}

base::Fraction::operator int32_t() const
{
	return static_cast<int32_t>(Div());
}

base::Fraction::operator int16_t() const
{
	return static_cast<int16_t>(Div());
}

base::Fraction::operator int8_t() const
{
	return static_cast<int8_t>(Div());
}

base::Fraction::operator double() const
{
	base::Fraction copy{*this};
	double int_part = static_cast<double>(copy.Div());
	copy -= copy.Div();
	double fraction_part = static_cast<double>(copy.Num()) / static_cast<double>(copy.Den());
	return int_part + fraction_part;
}

/* #endregion */

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
