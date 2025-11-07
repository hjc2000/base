#pragma once
#include "base/math/math.h"
#include "base/string/define.h"
#include "base/string/ICanToString.h"
#include <cstdint>
#include <numbers>
#include <numeric>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace base
{
	///
	/// @brief 分数类
	///
	class Int64Fraction final :
		public base::ICanToString
	{
	private:
		int64_t _num = 0;
		int64_t _den = 1;

	public:
		/* #region 构造函数 */

		///
		/// @brief 默认构造，分子为 0，分母为 1.
		///
		constexpr Int64Fraction() = default;

		///
		/// @brief 从整型值构造。分子为 num, 分母为 1.
		///
		/// @param num 分子。
		///
		template <typename T>
			requires(std::is_integral_v<T>)
		constexpr Int64Fraction(T int_num)
		{
			_num = int_num;
			_den = 1;
		}

		///
		/// @brief 通过浮点数构造。
		///
		/// @param value
		///
		template <typename T>
			requires(std::is_same_v<T, double>)
		constexpr Int64Fraction(T double_value)
		{
			if (double_value == 0.0)
			{
				_num = 0;
				_den = 1;
				return;
			}

			// 要保证分数计算过程不溢出，需要保证 factor * double_value <= INT64_MAX.
			int64_t factor = INT64_MAX / base::ceil(double_value);

			base::Int64Fraction int_part{static_cast<int64_t>(double_value)};
			double_value -= static_cast<double>(int_part);

			double_value *= factor;
			base::Int64Fraction fractional_part{static_cast<int64_t>(double_value), factor};

			*this += int_part + fractional_part;
		}

		///
		/// @brief 通过浮点数构造。
		///
		/// @param value
		///
		template <typename T>
			requires(std::is_same_v<T, float>)
		constexpr Int64Fraction(T float_value)
		{
			if (float_value == 0.0f)
			{
				_num = 0;
				_den = 1;
				return;
			}

			// 要保证分数计算过程不溢出，需要保证 factor * float_value <= INT64_MAX.
			int64_t factor = INT64_MAX / base::ceil(float_value);

			base::Int64Fraction int_part{static_cast<int64_t>(float_value)};
			float_value -= static_cast<float>(int_part);

			float_value *= factor;
			base::Int64Fraction fractional_part{static_cast<int64_t>(float_value), factor};

			*this += int_part + fractional_part;
		}

		///
		/// @brief 通过分子，分母进行构造。
		/// @param num 分子
		/// @param den 分母
		///
		constexpr Int64Fraction(int64_t num, int64_t den)
		{
			_num = num;
			if (num == 0)
			{
				_den = 1;
			}
			else
			{
				_den = den;
				Simplify();
			}
		}

		/* #endregion */

		/* #region 分子分母 */

		///
		/// @brief 获取分子。
		///
		/// @return
		///
		constexpr int64_t Num() const
		{
			return _num;
		}

		///
		/// @brief 获取分母。
		///
		/// @return
		///
		constexpr int64_t Den() const
		{
			return _den;
		}

		/* #endregion */

		/* #region 计算函数 */

		///
		/// @brief 化简。
		///
		constexpr void Simplify()
		{
			if (_num == 0)
			{
				_den = 1;
				return;
			}

			// 分子分母同时除以最大公约数
			int64_t gcd_value = std::gcd(_num, _den);
			int64_t scaled_num = _num / gcd_value;
			int64_t scaled_den = _den / gcd_value;

			if (scaled_den < 0)
			{
				// 如果分母小于 0，分子分母同时取相反数，保证分母为正。
				scaled_num = -scaled_num;
				scaled_den = -scaled_den;
			}

			_num = scaled_num;
			_den = scaled_den;
		}

		///
		/// @brief 倒数
		///
		/// @return
		///
		constexpr Int64Fraction Reciprocal() const
		{
			base::Int64Fraction ret{_den, _num};
			return ret;
		}

		///
		/// @brief 取绝对值。
		///
		/// @return
		///
		constexpr Int64Fraction Abs() const
		{
			if (*this < 0)
			{
				return -*this;
			}

			return *this;
		}

		///
		/// @brief 向下取整
		/// @return
		///
		constexpr int64_t Floor() const
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
				// 因为 C++ 除法近 0 截断，所以如果 Div > 0 ，本来就是向下取整了，
				// 不用再额外的操作了。
				//
				// Div = 0 就更不用说了，也不用什么额外的操作，直接返回 0 就完事了。
			}

			return ret;
		}

		///
		/// @brief 向上取整
		/// @return
		///
		constexpr int64_t Ceil() const
		{
			int64_t ret = Div();
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
		/// @return
		///
		constexpr int64_t Div() const
		{
			return _num / _den;
		}

		///
		/// @brief 获取分子除以分母的余数
		/// @return
		///
		constexpr int64_t Mod() const
		{
			return _num % _den;
		}

		///
		/// @brief 降低分辨率。
		///
		/// @param resolution
		///
		constexpr void ReduceResolution(base::Int64Fraction const &resolution)
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
				int64_t multiple = _den / resolution._den;

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
				int64_t multiple = resolution._den / _den;
				int64_t div = resolution._num / multiple;
				if (div != 0)
				{
					_num = _num / div * div;
				}
			}

			Simplify();
		}

		/* #endregion */

		constexpr Int64Fraction operator-() const
		{
			Int64Fraction ret{-_num, _den};
			return ret;
		}

		/* #region 四则运算符 */

		constexpr Int64Fraction operator+(Int64Fraction const &value) const
		{
			// 通分后的分母为本对象的分母和 value 的分母的最小公倍数
			int64_t scaled_den = std::lcm(_den, value.Den());

			// 通分后的分子为本对象的分子乘上分母所乘的倍数
			int64_t scaled_num = _num * (scaled_den / _den);
			int64_t value_scaled_num = value.Num() * (scaled_den / value.Den());

			Int64Fraction ret{
				scaled_num + value_scaled_num,
				scaled_den,
			};

			return ret;
		}

		constexpr Int64Fraction operator-(Int64Fraction const &value) const
		{
			Int64Fraction ret = *this + (-value);
			return ret;
		}

		constexpr Int64Fraction operator*(Int64Fraction const &value) const
		{
			base::Int64Fraction ret{
				_num * value.Num(),
				_den * value.Den(),
			};

			return ret;
		}

		constexpr Int64Fraction operator/(Int64Fraction const &value) const
		{
			Int64Fraction ret{*this * value.Reciprocal()};
			return ret;
		}

		/* #endregion */

		/* #region 自改变四则运算符 */

		constexpr Int64Fraction &operator+=(Int64Fraction const &value)
		{
			*this = *this + value;
			return *this;
		}

		constexpr Int64Fraction &operator-=(Int64Fraction const &value)
		{
			*this = *this - value;
			return *this;
		}

		constexpr Int64Fraction &operator*=(Int64Fraction const &value)
		{
			*this = *this * value;
			return *this;
		}

		constexpr Int64Fraction &operator/=(Int64Fraction const &value)
		{
			*this = *this / value;
			return *this;
		}

		/* #endregion */

		///
		/// @brief 将分数转化为字符串
		/// @return
		///
		virtual std::string ToString() const override
		{
			return std::to_string(_num) + " / " + std::to_string(_den);
		}

		/* #region 强制转换运算符 */

		constexpr explicit operator int64_t() const
		{
			return Div();
		}

		constexpr explicit operator uint64_t() const
		{
			return static_cast<uint64_t>(Div());
		}

		constexpr explicit operator int32_t() const
		{
			return static_cast<int32_t>(Div());
		}

		constexpr explicit operator uint32_t() const
		{
			return static_cast<uint32_t>(Div());
		}

		constexpr explicit operator int16_t() const
		{
			return static_cast<int16_t>(Div());
		}

		constexpr explicit operator uint16_t() const
		{
			return static_cast<uint16_t>(Div());
		}

		constexpr explicit operator int8_t() const
		{
			return static_cast<int8_t>(Div());
		}

		constexpr explicit operator uint8_t() const
		{
			return static_cast<uint8_t>(Div());
		}

		constexpr explicit operator double() const
		{
			base::Int64Fraction copy{*this};
			double int_part = static_cast<double>(copy.Div());
			copy -= copy.Div();
			double fraction_part = static_cast<double>(copy.Num()) / static_cast<double>(copy.Den());
			return int_part + fraction_part;
		}

		constexpr explicit operator float() const
		{
			base::Int64Fraction copy{*this};
			float int_part = static_cast<float>(copy.Div());
			copy -= copy.Div();
			float fraction_part = static_cast<float>(copy.Num()) / static_cast<float>(copy.Den());
			return int_part + fraction_part;
		}

		/* #endregion */

		/* #region 比较 */

		///
		/// @brief 本对象等于 another.
		/// @param another
		/// @return
		///
		constexpr bool operator==(Int64Fraction const &another) const
		{
			if (Num() == 0 && another.Num() == 0)
			{
				// 2 个分子都为 0 直接返回相等，这样更加安全，避免分子都为 0
				// 分母不相等时错误地将两个分数判断为不相等。
				return true;
			}

			return Num() == another.Num() && Den() == another.Den();
		}

		///
		/// @brief 本对象大于 another.
		/// @param another
		/// @return
		///
		constexpr bool operator>(Int64Fraction const &another) const
		{
			int64_t num1{Num()};
			int64_t den1{Den()};
			int64_t num2{another.Num()};
			int64_t den2{another.Den()};
			return num1 * den2 > num2 * den1;
		}

		///
		/// @brief 本对象小于 another.
		/// @param another
		/// @return
		///
		constexpr bool operator<(Int64Fraction const &another) const
		{
			int64_t num1{Num()};
			int64_t den1{Den()};
			int64_t num2{another.Num()};
			int64_t den2{another.Den()};
			return num1 * den2 < num2 * den1;
		}

		///
		/// @brief 本对象大于等于 another.
		///
		/// @param another
		///
		/// @return
		///
		constexpr bool operator>=(Int64Fraction const &another) const
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

		///
		/// @brief 本对象小于等于 another.
		///
		/// @param another
		///
		/// @return
		///
		constexpr bool operator<=(Int64Fraction const &another) const
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
	};

	namespace constant
	{
		///
		/// @brief 圆周率 Π.
		///
		/// @return
		///
		constexpr base::Int64Fraction pi{std::numbers::pi};

		///
		/// @brief 自然对数 ln 的底。
		///
		///
		constexpr base::Int64Fraction e{std::numbers::e};

	} // namespace constant

	///
	/// @brief 取绝对值。
	///
	/// @param value
	/// @return
	///
	constexpr base::Int64Fraction abs(base::Int64Fraction const &value)
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
	constexpr int64_t floor(base::Int64Fraction const &value)
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
	constexpr int64_t ceil(base::Int64Fraction const &value)
	{
		return value.Ceil();
	}

	///
	/// @brief 降低分辨率。
	///
	/// @return 降低分辨率后的值。
	///
	constexpr base::Int64Fraction reduce_resolution(base::Int64Fraction const &value,
													base::Int64Fraction const &resolution)
	{
		base::Int64Fraction copy = value;
		copy.ReduceResolution(resolution);
		return copy;
	}

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
inline base::Int64Fraction operator+(int64_t left, base::Int64Fraction const &right)
{
	return base::Int64Fraction{left} + right;
}

///
/// @brief 减
///
/// @param left
/// @param right
///
/// @return
///
inline base::Int64Fraction operator-(int64_t left, base::Int64Fraction const &right)
{
	return base::Int64Fraction{left} - right;
}

///
/// @brief 乘
///
/// @param left
/// @param right
///
/// @return
///
inline base::Int64Fraction operator*(int64_t left, base::Int64Fraction const &right)
{
	return base::Int64Fraction(left) * right;
}

///
/// @brief 除
///
/// @param left
/// @param right
///
/// @return
///
inline base::Int64Fraction operator/(int64_t left, base::Int64Fraction const &right)
{
	return base::Int64Fraction{left} / right;
}

/* #endregion */
