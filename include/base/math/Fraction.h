#pragma once
#include "base/bit/DoubleBitView.h"
#include "base/bit/FloatBitView.h"
#include "base/math/FastInt64Fraction.h"
#include "base/math/math.h"
#include "base/string/define.h"
#include "base/string/ICanToString.h"
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <string>

namespace base
{
	///
	/// @brief 分数类
	///
	class Fraction final :
		public base::ICanToString
	{
	private:
		base::BigInteger _num = 0;
		base::BigInteger _den = 1;

	public:
		class Constant;

		/* #region 构造函数 */

		///
		/// @brief 默认构造，分子为 0，分母为 1.
		///
		Fraction() = default;

		///
		/// @brief 从整型值构造。分子为 int_num, 分母为 1.
		///
		/// @param int_num 分子。
		///
		template <typename T>
			requires(std::is_integral_v<T>)
		Fraction(T int_num)
		{
			_num = int_num;
			_den = 1;
		}

		///
		/// @brief 通过浮点数构造。
		///
		/// @param double_value
		///
		template <typename T>
			requires(std::is_same_v<T, double>)
		Fraction(T double_value)
		{
			if (double_value == 0)
			{
				_num = 0;
				_den = 1;
				return;
			}

			base::bit::DoubleBitView view{double_value};

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

					base::Fraction value = f1 * (f2 + 1);
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

		///
		/// @brief 通过浮点数构造。
		///
		/// @param float_value
		///
		template <typename T>
			requires(std::is_same_v<T, float>)
		Fraction(T float_value)
		{
			if (float_value == 0)
			{
				_num = 0;
				_den = 1;
				return;
			}

			base::bit::FloatBitView view{float_value};

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

					base::Fraction value = f1 * (f2 + 1);
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

		///
		/// @brief 从大整型构造，则分子为 big_int_num, 分母为 1.
		///
		/// @param big_int_num
		///
		template <typename T>
			requires(std::is_same_v<T, base::BigInteger>)
		Fraction(T const &big_int_num)
		{
			_num = big_int_num;
			_den = 1;
		}

		///
		/// @brief 从 base::FastInt64Fraction 类型构造。
		///
		/// @param fast_int64_frac
		///
		template <typename T>
			requires(std::is_same_v<T, base::FastInt64Fraction>)
		Fraction(T const &fast_int64_frac)
		{
			_num = fast_int64_frac.Num();
			_den = fast_int64_frac.Den();
			Simplify();
		}

		///
		/// @brief 通过分子，分母进行构造。
		/// @param num 分子
		/// @param den 分母
		///
		Fraction(base::BigInteger const &num, base::BigInteger const &den)
		{
			_num = num;
			if (num == 0)
			{
				_den = 1;
				return;
			}

			if (den == 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "分母不能为 0."};
			}

			_den = den;
			Simplify();
		}

		/* #endregion */

		/* #region 分子分母 */

		///
		/// @brief 获取分子。
		///
		/// @return
		///
		base::BigInteger Num() const
		{
			return _num;
		}

		///
		/// @brief 获取分母。
		///
		/// @return
		///
		base::BigInteger Den() const
		{
			return _den;
		}

		/* #endregion */

		/* #region 计算函数 */

		///
		/// @brief 化简。
		///
		void Simplify()
		{
			if (_num == 0)
			{
				_den = 1;
				return;
			}

			// 分子分母同时除以最大公约数
			base::BigInteger gcd_value = base::gcd(_num, _den);
			_num /= gcd_value;
			_den /= gcd_value;

			if (_den < 0)
			{
				// 如果分母小于 0，分子分母同时取相反数，保证分母为正。
				_num = -_num;
				_den = -_den;
			}
		}

		///
		/// @brief 倒数
		///
		/// @return
		///
		Fraction Reciprocal() const
		{
			base::Fraction ret{_den, _num};
			return ret;
		}

		///
		/// @brief 取绝对值。
		///
		/// @return
		///
		Fraction Abs() const
		{
			if (*this < 0)
			{
				return -*this;
			}

			return *this;
		}

		///
		/// @brief 向下取整
		///
		/// @return
		///
		base::BigInteger Floor() const
		{
			base::BigInteger ret = Div();
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

		///
		/// @brief 向上取整
		///
		/// @return
		///
		base::BigInteger Ceil() const
		{
			base::BigInteger ret = Div();
			if (*this > 0)
			{
				if (Mod())
				{
					ret += 1;
				}
			}

			return ret;
		}

		///
		/// @brief 获取分子除以分母的值
		///
		/// @return
		///
		base::BigInteger Div() const
		{
			return _num / _den;
		}

		///
		/// @brief 获取分子除以分母的余数
		///
		/// @return
		///
		base::BigInteger Mod() const
		{
			return _num % _den;
		}

		///
		/// @brief 降低分辨率。
		///
		/// @param resolution
		///
		void ReduceResolution(base::Fraction const &resolution)
		{
			if (resolution <= 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "分辨率不能 <= 0."};
			}

			// 分辨率调整算法默认分母为正数，所以需要先规范化，如果分数是负数的话，
			// 需要将负号转移到分子上。
			if (_den < 0)
			{
				_num = -_num;
				_den = -_den;
			}

			base::Fraction resolution_copy = resolution;
			if (resolution_copy._den < 0)
			{
				resolution_copy._num = -resolution_copy._num;
				resolution_copy._den = -resolution_copy._den;
			}

			if (_den >= resolution_copy._den)
			{
				// 本分数的分母比 resolution_copy 的分母大，说明本分数的分辨率大于
				// resolution_copy.
				//
				// 首先需要减小本分数的分母，将分辨率降下来。分子分母同时除以一个系数进行截断，
				// 从而降低分辨率。
				base::BigInteger multiple = _den / resolution_copy._den;

				// 首先将分辨率降低到 1 / resolution_copy._den.
				_num /= multiple;
				_den /= multiple;

				// 如果 resolution_copy._num > 1, 则还不够，刚才的分辨率降低到
				// 1 / resolution_copy._den 了，还要继续降低。
				_num = _num / resolution_copy._num * resolution_copy._num;
			}
			else
			{
				// 本分数的分母比 resolution_copy 的分母小。但这不能说明本分数的分辨率小于
				// resolution_copy, 因为 resolution_copy 的分子可能较大。
				//
				// 将 resolution_copy 的分子分母同时除以一个系数，将 resolution_copy
				// 的分母调整到与本分数的分母相等，然后看一下调整后的 resolution_copy
				// 的分子，如果不等于 0, 即没有被截断成 0, 说明原本的分子确实较大，
				// 大到足以放大 resolution_copy 的大分母所导致的小步长，导致步长很大，分辨率低。
				// 这种情况下本分数的分辨率才是高于 resolution_copy, 才需要降低分辨率。
				base::BigInteger multiple = resolution_copy._den / _den;
				base::BigInteger div = resolution_copy._num / multiple;
				if (div != 0)
				{
					_num = _num / div * div;
				}
			}

			Simplify();
		}

		/* #endregion */

		Fraction operator-() const
		{
			Fraction ret{-_num, _den};
			return ret;
		}

		/* #region 四则运算符 */

		Fraction operator+(Fraction const &value) const
		{
			// 通分后的分母为本对象的分母和 value 的分母的最小公倍数
			base::BigInteger scaled_den = base::lcm(_den, value.Den());

			// 通分后的分子为本对象的分子乘上分母所乘的倍数
			base::BigInteger scaled_num1 = _num * (scaled_den / _den);
			base::BigInteger scaled_num2 = value.Num() * (scaled_den / value.Den());

			Fraction ret{
				scaled_num1 + scaled_num2,
				scaled_den,
			};

			return ret;
		}

		Fraction operator-(Fraction const &value) const
		{
			Fraction ret = *this + (-value);
			return ret;
		}

		Fraction operator*(Fraction const &value) const
		{
			base::Fraction ret{
				_num * value.Num(),
				_den * value.Den(),
			};

			return ret;
		}

		Fraction operator/(Fraction const &value) const
		{
			Fraction ret{*this * value.Reciprocal()};
			return ret;
		}

		/* #endregion */

		/* #region 自改变四则运算符 */

		Fraction &operator+=(Fraction const &value)
		{
			*this = *this + value;
			return *this;
		}

		Fraction &operator-=(Fraction const &value)
		{
			*this = *this - value;
			return *this;
		}

		Fraction &operator*=(Fraction const &value)
		{
			*this = *this * value;
			return *this;
		}

		Fraction &operator/=(Fraction const &value)
		{
			*this = *this / value;
			return *this;
		}

		/* #endregion */

		///
		/// @brief 将分数转化为字符串
		///
		/// @return
		///
		virtual std::string ToString() const override
		{
			return base::to_string(_num) + " / " + base::to_string(_den);
		}

		/* #region 强制转换运算符 */

		explicit operator base::BigInteger() const
		{
			return Div();
		}

		explicit operator int64_t() const
		{
			return static_cast<int64_t>(Div());
		}

		explicit operator uint64_t() const
		{
			return static_cast<uint64_t>(Div());
		}

		explicit operator int32_t() const
		{
			return static_cast<int32_t>(Div());
		}

		explicit operator uint32_t() const
		{
			return static_cast<uint32_t>(Div());
		}

		explicit operator int16_t() const
		{
			return static_cast<int16_t>(Div());
		}

		explicit operator uint16_t() const
		{
			return static_cast<uint16_t>(Div());
		}

		explicit operator int8_t() const
		{
			return static_cast<int8_t>(Div());
		}

		explicit operator uint8_t() const
		{
			return static_cast<uint8_t>(Div());
		}

		explicit operator double() const
		{
			base::Fraction copy{*this};
			base::BigInteger div = copy.Div();

			// 取出整数部分。
			double int_part = static_cast<double>(div);

			// 取出整数部分后减掉整数部分。
			copy -= div;

			// 取出小数部分。
			double fraction_part = static_cast<double>(copy.Num()) / static_cast<double>(copy.Den());
			return int_part + fraction_part;
		}

		explicit operator float() const
		{
			base::Fraction copy{*this};
			base::BigInteger div = copy.Div();

			// 取出整数部分。
			float int_part = static_cast<float>(div);

			// 取出整数部分后减掉整数部分。
			copy -= div;

			// 取出小数部分。
			float fraction_part = static_cast<float>(copy.Num()) / static_cast<float>(copy.Den());
			return int_part + fraction_part;
		}

		explicit operator base::FastInt64Fraction() const
		{
			base::Fraction copy{*this};

			base::Fraction resolution{
				1,
				std::numeric_limits<int64_t>::max(),
			};

			copy.ReduceResolution(resolution);

			return base::FastInt64Fraction{
				static_cast<int64_t>(_num),
				static_cast<int64_t>(_den),
			};
		}

		/* #endregion */

		/* #region 比较 */

		///
		/// @brief 本对象等于 other.
		///
		/// @param other
		///
		/// @return
		///
		bool operator==(Fraction const &other) const
		{
			return Num() * other.Den() == other.Num() * Den();
		}

		///
		/// @brief 本对象大于 other.
		///
		/// @param other
		///
		/// @return
		///
		bool operator>(Fraction const &other) const
		{
			return Num() * other.Den() > other.Num() * Den();
		}

		///
		/// @brief 本对象小于 other.
		///
		/// @param other
		///
		/// @return
		///
		bool operator<(Fraction const &other) const
		{
			return Num() * other.Den() < other.Num() * Den();
		}

		///
		/// @brief 本对象大于等于 other.
		///
		/// @param other
		///
		/// @return
		///
		bool operator>=(Fraction const &other) const
		{
			return Num() * other.Den() >= other.Num() * Den();
		}

		///
		/// @brief 本对象小于等于 other.
		///
		/// @param other
		///
		/// @return
		///
		bool operator<=(Fraction const &other) const
		{
			return Num() * other.Den() <= other.Num() * Den();
		}

		/* #endregion */

	}; // class Fraction

	class Fraction::Constant
	{
	public:
		///
		/// @brief 圆周率 Π.
		///
		/// @return
		///
		static base::Fraction pi()
		{
			// 使用 64 位整型分辨率的分数精度是够的，标准库自带的 pi 的 double 常数转换为
			// 分数，分子分母只需要用 64 位整型就能表示。
			base::Fraction ret{base::FastInt64Fraction::Constant::pi()};
			return ret;
		}

		///
		/// @brief 欧拉常数 e, 或者叫自然常数，或者自然对数 ln 的底。
		///
		/// @return
		///
		static base::Fraction e()
		{
			// 使用 64 位整型分辨率的分数精度是够的，标准库自带的 e 的 double 常数转换为
			// 分数，分子分母只需要用 64 位整型就能表示。
			base::Fraction ret{base::FastInt64Fraction::Constant::e()};
			return ret;
		}

		///
		/// @brief 水的比热容。
		///
		/// @note 4.187 kJ/(kg·K)
		///
		/// @return
		///
		static base::Fraction specific_heat_capacity_of_water()
		{
			base::Fraction ret{base::FastInt64Fraction::Constant::specific_heat_capacity_of_water()};
			return ret;
		}

		///
		/// @brief 普朗克常数。
		///
		/// @return
		///
		static base::Fraction h()
		{
			base::Fraction ret{
				662607015,
				base::pow<base::BigInteger>(10, 42),
			};

			return ret;
		}
	};

	/* #region 数学函数 */

	///
	/// @brief 取绝对值。
	///
	/// @param value
	///
	/// @return
	///
	inline base::Fraction abs(base::Fraction const &value)
	{
		return value.Abs();
	}

	///
	/// @brief 向下取整
	///
	/// @param value
	///
	/// @return
	///
	inline base::BigInteger floor(base::Fraction const &value)
	{
		return value.Floor();
	}

	///
	/// @brief 向上取整
	///
	/// @param value
	///
	/// @return
	///
	inline base::BigInteger ceil(base::Fraction const &value)
	{
		return value.Ceil();
	}

	///
	/// @brief 降低分辨率。
	///
	/// @return 降低分辨率后的值。
	///
	inline base::Fraction reduce_resolution(base::Fraction const &value,
											base::Fraction const &resolution)
	{
		base::Fraction copy = value;
		copy.ReduceResolution(resolution);
		return copy;
	}

	/* #endregion */

} // namespace base

/* #region 全局四则运算符 */

///
/// @brief 加
///
/// @param left
/// @param right
///
/// @return
///
inline base::Fraction operator+(base::BigInteger left, base::Fraction const &right)
{
	return base::Fraction{left} + right;
}

///
/// @brief 减
///
/// @param left
/// @param right
///
/// @return
///
inline base::Fraction operator-(base::BigInteger left, base::Fraction const &right)
{
	return base::Fraction{left} - right;
}

///
/// @brief 乘
///
/// @param left
/// @param right
///
/// @return
///
inline base::Fraction operator*(base::BigInteger left, base::Fraction const &right)
{
	return base::Fraction(left) * right;
}

///
/// @brief 除
///
/// @param left
/// @param right
///
/// @return
///
inline base::Fraction operator/(base::BigInteger left, base::Fraction const &right)
{
	return base::Fraction{left} / right;
}

/* #endregion */
