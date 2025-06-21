#include "Fraction.h"
#include "base/math/pow.h"

base::Fraction::Fraction(base::Double const &value)
{
	if (value.Value() == 0.0)
	{
		SetNum(0);
		SetDen(1);
		return;
	}

	double db = value.Value();
	int loop_times = 0;
	constexpr uint64_t factor = base::pow<uint64_t>(2, 63);
	while (db != 0.0)
	{
		base::BigInteger int_part{static_cast<int64_t>(db)};
		base::Fraction temp{int_part, base::pow<base::BigInteger>(factor, loop_times)};
		(*this) += temp;
		db -= static_cast<double>(int_part);
		db *= factor;
		++loop_times;
	}
}

void base::Fraction::Simplify()
{
	if (_den == 0)
	{
		throw std::invalid_argument{"分母不能为 0."};
	}

	if (_num == 0)
	{
		_den = 1;
		return;
	}

	// 分子分母同时除以最大公约数
	base::BigInteger gcd_value = boost::multiprecision::gcd(_num, _den);
	base::BigInteger scaled_num = _num / gcd_value;
	base::BigInteger scaled_den = _den / gcd_value;

	if (scaled_den < 0)
	{
		// 如果分母小于 0，分子分母同时取相反数
		scaled_num = -scaled_num;
		scaled_den = -scaled_den;
	}

	_num = scaled_num;
	_den = scaled_den;
}

/* #region 四则运算符 */

base::Fraction base::Fraction::operator+(Fraction const &value) const
{
	// 通分后的分母为本对象的分母和 value 的分母的最小公倍数
	base::BigInteger scaled_den = boost::multiprecision::lcm(_den, value.Den());

	// 通分后的分子为本对象的分子乘上分母所乘的倍数
	base::BigInteger scaled_num = _num * (scaled_den / _den);
	base::BigInteger value_scaled_num = value.Num() * (scaled_den / value.Den());

	Fraction ret{
		scaled_num + value_scaled_num,
		scaled_den,
	};

	return ret.SimplifiedForm();
}

base::Fraction base::Fraction::operator-(Fraction const &value) const
{
	Fraction ret = *this + (-value);
	return ret.SimplifiedForm();
}

base::Fraction base::Fraction::operator*(Fraction const &value) const
{
	base::Fraction ret;
	ret.SetNum(_num * value.Num());
	ret.SetDen(_den * value.Den());
	return ret.SimplifiedForm();
}

base::Fraction base::Fraction::operator/(Fraction const &value) const
{
	Fraction ret{*this * value.Reciprocal()};
	return ret.SimplifiedForm();
}

/* #endregion */

std::string base::Fraction::ToString() const
{
	return base::to_string(_num) + " / " + base::to_string(_den);
}

base::Fraction::operator double() const
{
	base::Fraction copy{*this};
	double int_part = static_cast<double>(copy.Div());
	copy -= copy.Div();
	double fraction_part = static_cast<double>(copy.Num()) / static_cast<double>(copy.Den());
	return int_part + fraction_part;
}

/* #region 比较运算符 */

bool base::Fraction::operator==(Fraction const &another) const
{
	if (Num() == 0 && another.Num() == 0)
	{
		/* 2 个分子都为 0 直接返回相等，这样更加安全，避免分子都为 0
		 * 分母不相等时错误地将两个分数判断为不相等。
		 */
		return true;
	}

	Fraction f1 = SimplifiedForm();
	Fraction f2 = another.SimplifiedForm();
	return f1.Num() == f2.Num() && f1.Den() == f2.Den();
}

bool base::Fraction::operator>(Fraction const &another) const
{
	// 先化简，避免分母为负数，然后使用交叉乘法比大小。
	Fraction f1 = SimplifiedForm();
	Fraction f2 = another.SimplifiedForm();
	base::BigInteger num1{f1.Num()};
	base::BigInteger den1{f1.Den()};
	base::BigInteger num2{f2.Num()};
	base::BigInteger den2{f2.Den()};
	return num1 * den2 > num2 * den1;
}

bool base::Fraction::operator<(Fraction const &another) const
{
	// 先化简，避免分母为负数，然后使用交叉乘法比大小。
	Fraction f1 = SimplifiedForm();
	Fraction f2 = another.SimplifiedForm();
	base::BigInteger num1{f1.Num()};
	base::BigInteger den1{f1.Den()};
	base::BigInteger num2{f2.Num()};
	base::BigInteger den2{f2.Den()};
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
