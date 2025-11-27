#include "Fraction.h"
#include "base/bit/DoubleBitView.h"
#include "base/bit/FloatBitView.h"
#include "base/string/define.h"
#include "BigInteger.h"
#include <stdexcept>

void base::Fraction::FromDouble(double value)
{
	if (value == 0)
	{
		_num = 0;
		_den = 1;
		return;
	}

	base::bit::DoubleBitView view{value};

	switch (view.ValueType())
	{
	case base::bit::FloatValueType::Normalized:
		{
			base::Fraction f1{
				base::BigInteger{1} << view.ExponentBits(),
				base::BigInteger{1} << 1023,
			};

			base::Fraction f2 = base::Fraction{
				view.MantissaBits(),
				base::BigInteger{1} << 52,
			};

			base::Fraction value = f1 * (1 + f2);
			if (view.Positive())
			{
				*this = value;
			}
			else
			{
				*this = -value;
			}

			break;
		}
	case base::bit::FloatValueType::Denormalized:
		{
			base::Fraction f1{
				base::BigInteger{2},
				base::BigInteger{1} << 1022,
			};

			base::Fraction f2 = base::Fraction{
				view.MantissaBits(),
				base::BigInteger{1} << 52,
			};

			base::Fraction value = f1 * f2;
			if (view.Positive())
			{
				*this = value;
			}
			else
			{
				*this = -value;
			}

			break;
		}
	case base::bit::FloatValueType::NaN:
		{
			throw std::invalid_argument{CODE_POS_STR + "此浮点数是 NaN."};
		}
	case base::bit::FloatValueType::PositiveInfinite:
		{
			throw std::invalid_argument{CODE_POS_STR + "此浮点数是正无穷。"};
		}
	case base::bit::FloatValueType::NegativeInfinite:
		{
			throw std::invalid_argument{CODE_POS_STR + "此浮点数是负无穷。"};
		}
	default:
		{
			throw std::runtime_error{CODE_POS_STR + "非法的枚举值。"};
		}
	}
}

void base::Fraction::FromFloat(float value)
{
	if (value == 0)
	{
		_num = 0;
		_den = 1;
		return;
	}

	base::bit::FloatBitView view{value};

	switch (view.ValueType())
	{
	case base::bit::FloatValueType::Normalized:
		{
			base::Fraction f1{
				base::BigInteger{1} << view.ExponentBits(),
				base::BigInteger{1} << 127,
			};

			base::Fraction f2 = base::Fraction{
				view.MantissaBits(),
				base::BigInteger{1} << 23,
			};

			base::Fraction value = f1 * (1 + f2);
			if (view.Positive())
			{
				*this = value;
			}
			else
			{
				*this = -value;
			}

			break;
		}
	case base::bit::FloatValueType::Denormalized:
		{
			base::Fraction f1{
				base::BigInteger{2},
				base::BigInteger{1} << 126,
			};

			base::Fraction f2 = base::Fraction{
				view.MantissaBits(),
				base::BigInteger{1} << 23,
			};

			base::Fraction value = f1 * f2;
			if (view.Positive())
			{
				*this = value;
			}
			else
			{
				*this = -value;
			}

			break;
		}
	case base::bit::FloatValueType::NaN:
		{
			throw std::invalid_argument{CODE_POS_STR + "此浮点数是 NaN."};
		}
	case base::bit::FloatValueType::PositiveInfinite:
		{
			throw std::invalid_argument{CODE_POS_STR + "此浮点数是正无穷。"};
		}
	case base::bit::FloatValueType::NegativeInfinite:
		{
			throw std::invalid_argument{CODE_POS_STR + "此浮点数是负无穷。"};
		}
	default:
		{
			throw std::runtime_error{CODE_POS_STR + "非法的枚举值。"};
		}
	}
}

void base::Fraction::Simplify()
{
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
		// 如果分母小于 0，分子分母同时取相反数，保证分母为正。
		scaled_num = -scaled_num;
		scaled_den = -scaled_den;
	}

	_num = scaled_num;
	_den = scaled_den;
}

void base::Fraction::ReduceResolution(base::Fraction const &resolution)
{
	if (resolution <= 0)
	{
		throw std::invalid_argument{CODE_POS_STR + "分辨率不能 <= 0."};
	}

	if (_den >= resolution._den)
	{
		// 本分数的分母比 resolution 的分母大，说明本分数的分辨率大于 resolution.
		//
		// 首先需要减小本分数的分母，将分辨率降下来。分子分母同时除以一个系数进行截断，
		// 从而降低分辨率。
		base::BigInteger multiple = _den / resolution._den;

		// 首先将分辨率降低到 1 / resolution._den.
		_num /= multiple;
		_den /= multiple;

		// 如果 resolution._num > 1, 则还不够，刚才的分辨率降低到 1 / resolution._den 了，
		// 还要继续降低。
		_num = _num / resolution._num * resolution._num;
	}
	else
	{
		// 本分数的分母比 resolution 的分母小。但这不能说明本分数的分辨率小于 resolution,
		// 因为 resolution 的分子可能较大。
		//
		// 将 resolution 的分子分母同时除以一个系数，将 resolution 的分母调整到与本分数的分母
		// 相等，然后看一下调整后的 resolution 的分子，如果不等于 0, 即没有被截断成 0, 说明原本的
		// 分子确实较大，大到足以放大 resolution 的大分母所导致的小步长，导致步长很大，分辨率低。
		// 这种情况下本分数的分辨率才是高于 resolution, 才需要降低分辨率。
		base::BigInteger multiple = resolution._den / _den;
		base::BigInteger div = resolution._num / multiple;
		if (div != 0)
		{
			_num = _num / div * div;
		}
	}

	Simplify();
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

	return ret;
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

base::Fraction::operator float() const
{
	base::Fraction copy{*this};
	float int_part = static_cast<float>(copy.Div());
	copy -= copy.Div();
	float fraction_part = static_cast<float>(copy.Num()) / static_cast<float>(copy.Den());
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

	return Num() == another.Num() && Den() == another.Den();
}

bool base::Fraction::operator>(Fraction const &another) const
{
	return Num() * another.Den() > another.Num() * Den();
}

bool base::Fraction::operator<(Fraction const &another) const
{
	return Num() * another.Den() < another.Num() * Den();
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
