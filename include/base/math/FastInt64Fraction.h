#pragma once
#include "base/math/math.h"
#include "base/string/define.h"
#include "base/string/ICanToString.h"
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace base
{
	///
	/// @brief 分数类
	///
	class FastInt64Fraction final :
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
		constexpr FastInt64Fraction() = default;

		///
		/// @brief 从整型值构造。分子为 num, 分母为 1.
		///
		/// @param num 分子。
		///
		template <typename T>
			requires(std::is_integral_v<T>)
		constexpr FastInt64Fraction(T int_num)
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
		constexpr FastInt64Fraction(T double_value)
		{
			if (double_value == 0)
			{
				_num = 0;
				_den = 1;
				return;
			}

			// 要保证分数计算过程不溢出，需要保证 factor * double_value <=  std::numeric_limits<int64_t>::max() .
			int64_t factor = std::numeric_limits<int64_t>::max() / base::ceil(double_value);

			base::FastInt64Fraction int_part{static_cast<int64_t>(double_value)};
			double_value -= static_cast<double>(int_part);

			double_value *= factor;
			base::FastInt64Fraction fractional_part{static_cast<int64_t>(double_value), factor};

			*this += int_part + fractional_part;
			Simplify();
		}

		///
		/// @brief 通过浮点数构造。
		///
		/// @param value
		///
		template <typename T>
			requires(std::is_same_v<T, float>)
		constexpr FastInt64Fraction(T float_value)
		{
			if (float_value == 0)
			{
				_num = 0;
				_den = 1;
				return;
			}

			// 要保证分数计算过程不溢出，需要保证 factor * float_value <=  std::numeric_limits<int64_t>::max() .
			int64_t factor = std::numeric_limits<int64_t>::max() / base::ceil(float_value);

			base::FastInt64Fraction int_part{static_cast<int64_t>(float_value)};
			float_value -= static_cast<float>(int_part);

			float_value *= factor;
			base::FastInt64Fraction fractional_part{static_cast<int64_t>(float_value), factor};

			*this += int_part + fractional_part;
			Simplify();
		}

		///
		/// @brief 通过分子，分母进行构造。
		/// @param num 分子
		/// @param den 分母
		///
		constexpr FastInt64Fraction(int64_t num, int64_t den)
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
			int64_t gcd_value = base::gcd(_num, _den);
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
		constexpr FastInt64Fraction Reciprocal() const
		{
			base::FastInt64Fraction ret{_den, _num};
			return ret;
		}

		///
		/// @brief 取绝对值。
		///
		/// @return
		///
		constexpr FastInt64Fraction Abs() const
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
		///
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
		///
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
		constexpr void ReduceResolution(base::FastInt64Fraction const &resolution)
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

			base::FastInt64Fraction resolution_copy = resolution;
			if (resolution_copy._den < 0)
			{
				resolution_copy._num = -resolution_copy._num;
				resolution_copy._den = -resolution_copy._den;
			}

			if (_den >= resolution_copy._den)
			{
				// 本分数的分母比 resolution_copy 的分母大，说明本分数的分辨率大于 resolution_copy.
				//
				// 首先需要减小本分数的分母，将分辨率降下来。分子分母同时除以一个系数进行截断，
				// 从而降低分辨率。
				int64_t multiple = _den / resolution_copy._den;

				// 首先将分辨率降低到 1 / resolution_copy._den.
				_num /= multiple;
				_den /= multiple;

				// 如果 resolution_copy._num > 1, 则还不够，刚才的分辨率降低到
				// 1 / resolution_copy._den 了，
				// 还要继续降低。
				_num = _num / resolution_copy._num * resolution_copy._num;
			}
			else
			{
				// 本分数的分母比 resolution_copy 的分母小。但这不能说明本分数的分辨率小于
				// resolution_copy,
				// 因为 resolution_copy 的分子可能较大。
				//
				// 将 resolution_copy 的分子分母同时除以一个系数，将 resolution_copy
				// 的分母调整到与本分数的分母
				// 相等，然后看一下调整后的 resolution_copy 的分子，如果不等于 0,
				// 即没有被截断成 0, 说明原本的
				// 分子确实较大，大到足以放大 resolution_copy 的大分母所导致的小步长，
				// 导致步长很大，分辨率低。
				// 这种情况下本分数的分辨率才是高于 resolution_copy,
				// 才需要降低分辨率。
				int64_t multiple = resolution_copy._den / _den;
				int64_t div = resolution_copy._num / multiple;
				if (div != 0)
				{
					_num = _num / div * div;
				}
			}
		}

		/* #endregion */

		constexpr FastInt64Fraction operator-() const
		{
			FastInt64Fraction ret{-_num, _den};
			return ret;
		}

		/* #region 四则运算符 */

		///
		/// @brief 加法运算符。
		///
		/// @note 如果不会溢出，会直接执行快速加法，不执行缓慢的 lcm 了，直接用两个分母的积通分。
		///
		/// @note 执行加法后，即使没有溢出，分母也可能已经很大了，此时有 2 个选择，一个是尝试化简，
		/// 看能不能减小分母，另一个是降低分数的分辨率，这会造成精度损失，但是在性能比精度优先的场合，
		/// 例如滤波算法中降低分辨率是合适的。
		///
		/// @param value
		/// @return
		///
		constexpr FastInt64Fraction operator+(FastInt64Fraction const &value) const
		{
			base::FastInt64Fraction copy{*this};
			copy += value;
			return copy;
		}

		constexpr FastInt64Fraction operator-(FastInt64Fraction const &value) const
		{
			FastInt64Fraction ret = *this + (-value);
			return ret;
		}

		constexpr FastInt64Fraction operator*(FastInt64Fraction const &value) const
		{
			base::FastInt64Fraction copy{*this};
			copy *= value;
			return copy;
		}

		constexpr FastInt64Fraction operator/(FastInt64Fraction const &value) const
		{
			base::FastInt64Fraction copy{*this};
			copy /= value;
			return copy;
		}

		/* #endregion */

		/* #region 自改变四则运算符 */

		constexpr FastInt64Fraction &operator+=(FastInt64Fraction const &value)
		{
			if (_den < 0)
			{
				_num = -_num;
				_den = -_den;
			}

			base::FastInt64Fraction copyed_value = value;

			if (copyed_value._den < 0)
			{
				copyed_value._num = -copyed_value._num;
				copyed_value._den = -copyed_value._den;
			}

			if (_den == copyed_value.Den())
			{
				_num += copyed_value.Num();
				return *this;
			}

			if (_den > copyed_value.Den() && _den % copyed_value.Den() == 0)
			{
				int64_t multiple = _den / copyed_value.Den();
				_num += copyed_value.Num() * multiple;
				return *this;
			}

			if (copyed_value.Den() > _den && copyed_value.Den() % _den == 0)
			{
				int64_t multiple = copyed_value.Den() / _den;
				_num *= multiple;
				_den *= multiple;
				_num += copyed_value.Num();
				return *this;
			}

			if (std::numeric_limits<int64_t>::max() / _den > copyed_value.Den())
			{
				// 不会溢出就执行快速加法，不执行缓慢的 lcm 了，直接用两个分母的积通分。
				int64_t scaled_den = _den * copyed_value.Den();

				int64_t scaled_num1 = _num * copyed_value.Den();
				int64_t scaled_num2 = copyed_value.Num() * _den;

				_num = scaled_num1 + scaled_num2;
				_den = scaled_den;
				return *this;
			}

			// 通分后的分母为本对象的分母和 copyed_value 的分母的最小公倍数
			int64_t scaled_den = base::lcm(_den, copyed_value.Den());

			// 通分后的分子为本对象的分子乘上分母所乘的倍数
			int64_t scaled_num1 = _num * (scaled_den / _den);
			int64_t scaled_num2 = copyed_value.Num() * (scaled_den / copyed_value.Den());

			_num = scaled_num1 + scaled_num2;
			_den = scaled_den;
			return *this;
		}

		constexpr FastInt64Fraction &operator-=(FastInt64Fraction const &value)
		{
			*this += -value;
			return *this;
		}

		constexpr FastInt64Fraction &operator*=(FastInt64Fraction const &value)
		{
			_num *= value.Num();
			_den *= value.Den();
			return *this;
		}

		constexpr FastInt64Fraction &operator/=(FastInt64Fraction const &value)
		{
			*this *= value.Reciprocal();
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
			base::FastInt64Fraction copy{*this};
			copy.Simplify();

			double int_part = static_cast<double>(copy.Div());
			copy -= copy.Div();
			double fraction_part = static_cast<double>(copy.Num()) / static_cast<double>(copy.Den());
			return int_part + fraction_part;
		}

		constexpr explicit operator float() const
		{
			base::FastInt64Fraction copy{*this};
			copy.Simplify();

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
		constexpr bool operator==(FastInt64Fraction const &another) const
		{
			return Num() * another.Den() == another.Num() * Den();
		}

		///
		/// @brief 本对象大于 another.
		/// @param another
		/// @return
		///
		constexpr bool operator>(FastInt64Fraction const &another) const
		{
			return Num() * another.Den() > another.Num() * Den();
		}

		///
		/// @brief 本对象小于 another.
		/// @param another
		/// @return
		///
		constexpr bool operator<(FastInt64Fraction const &another) const
		{
			return Num() * another.Den() < another.Num() * Den();
		}

		///
		/// @brief 本对象大于等于 another.
		///
		/// @param another
		///
		/// @return
		///
		constexpr bool operator>=(FastInt64Fraction const &another) const
		{
			return Num() * another.Den() >= another.Num() * Den();
		}

		///
		/// @brief 本对象小于等于 another.
		///
		/// @param another
		///
		/// @return
		///
		constexpr bool operator<=(FastInt64Fraction const &another) const
		{
			return Num() * another.Den() <= another.Num() * Den();
		}

		/* #endregion */
	};

	///
	/// @brief 取绝对值。
	///
	/// @param value
	/// @return
	///
	constexpr base::FastInt64Fraction abs(base::FastInt64Fraction const &value)
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
	constexpr int64_t floor(base::FastInt64Fraction const &value)
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
	constexpr int64_t ceil(base::FastInt64Fraction const &value)
	{
		return value.Ceil();
	}

	///
	/// @brief 降低分辨率。
	///
	/// @return 降低分辨率后的值。
	///
	constexpr base::FastInt64Fraction reduce_resolution(base::FastInt64Fraction const &value,
														base::FastInt64Fraction const &resolution)
	{
		base::FastInt64Fraction copy = value;
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
inline base::FastInt64Fraction operator+(int64_t left, base::FastInt64Fraction const &right)
{
	return base::FastInt64Fraction{left} + right;
}

///
/// @brief 减
///
/// @param left
/// @param right
///
/// @return
///
inline base::FastInt64Fraction operator-(int64_t left, base::FastInt64Fraction const &right)
{
	return base::FastInt64Fraction{left} - right;
}

///
/// @brief 乘
///
/// @param left
/// @param right
///
/// @return
///
inline base::FastInt64Fraction operator*(int64_t left, base::FastInt64Fraction const &right)
{
	return base::FastInt64Fraction(left) * right;
}

///
/// @brief 除
///
/// @param left
/// @param right
///
/// @return
///
inline base::FastInt64Fraction operator/(int64_t left, base::FastInt64Fraction const &right)
{
	return base::FastInt64Fraction{left} / right;
}

/* #endregion */
