#include "Fraction.h" // IWYU pragma: keep

std::string base::Fraction::ToString() const
{
	return std::to_string(_num) + " / " + std::to_string(_den);
}

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
