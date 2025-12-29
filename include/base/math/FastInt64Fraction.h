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

		void ScaleFromInt128(base::Int128 num, base::Int128 den)
		{
			if (den < 0)
			{
				num = -num;
				den = -den;
			}

			int64_t threshold = std::numeric_limits<int64_t>::max() / 2;

			if (den > threshold)
			{
				base::Int128 multiple = den / threshold;
				num /= multiple;
				den /= multiple;
			}

			if (base::abs(num) > threshold)
			{
				base::Int128 multiple = base::abs(num) / threshold;

				if (den / multiple == 0)
				{
					num /= den;
					den = 1;
				}
				else
				{
					num /= multiple;
					den /= multiple;
				}
			}

			_num = static_cast<int64_t>(num);
			_den = static_cast<int64_t>(den);
		}

	public:
		class Constant;

		/* #region 构造函数 */

		///
		/// @brief 默认构造，分子为 0，分母为 1.
		///
		FastInt64Fraction() = default;

		///
		/// @brief 从整型值构造。分子为 num, 分母为 1.
		///
		/// @param num 分子。
		///
		template <typename T>
			requires(std::is_integral_v<T>)
		FastInt64Fraction(T int_num)
		{
			_num = int_num;
			_den = 1;
		}

		///
		/// @brief 通过分子，分母进行构造。
		/// @param num 分子
		/// @param den 分母
		///
		FastInt64Fraction(int64_t num, int64_t den)
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
		int64_t Num() const
		{
			return _num;
		}

		///
		/// @brief 获取分母。
		///
		/// @return
		///
		int64_t Den() const
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
		FastInt64Fraction Reciprocal() const
		{
			base::FastInt64Fraction ret{_den, _num};
			return ret;
		}

		///
		/// @brief 取绝对值。
		///
		/// @return
		///
		FastInt64Fraction Abs() const
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
		int64_t Floor() const
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
		int64_t Ceil() const
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
		int64_t Div() const
		{
			return _num / _den;
		}

		///
		/// @brief 获取分子除以分母的余数
		/// @return
		///
		int64_t Mod() const
		{
			return _num % _den;
		}

		///
		/// @brief 降低分辨率。
		///
		/// @param resolution
		///
		void ReduceResolution(base::FastInt64Fraction const &resolution)
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
				_den = resolution_copy._den;

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

		FastInt64Fraction operator-() const
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
		FastInt64Fraction operator+(FastInt64Fraction const &value) const
		{
			base::FastInt64Fraction copy{*this};
			copy += value;
			return copy;
		}

		FastInt64Fraction operator-(FastInt64Fraction const &value) const
		{
			FastInt64Fraction ret = *this + (-value);
			return ret;
		}

		FastInt64Fraction operator*(FastInt64Fraction const &value) const
		{
			base::FastInt64Fraction copy{*this};
			copy *= value;
			return copy;
		}

		FastInt64Fraction operator/(FastInt64Fraction const &value) const
		{
			base::FastInt64Fraction copy{*this};
			copy /= value;
			return copy;
		}

		/* #endregion */

		/* #region 自改变四则运算符 */

		FastInt64Fraction &operator+=(FastInt64Fraction const &value)
		{
			base::Int128 num1 = _num;
			base::Int128 den1 = _den;
			if (den1 < 0)
			{
				num1 = -num1;
				den1 = -den1;
			}

			base::Int128 num2 = value.Num();
			base::Int128 den2 = value.Den();
			if (den2 < 0)
			{
				num2 = -num2;
				den2 = -den2;
			}

			if (den1 == den2)
			{
				ScaleFromInt128(num1 + num2, den1);
			}
			else
			{
				ScaleFromInt128(num1 * den2 + num2 * den1, den1 * den2);
			}

			return *this;
		}

		FastInt64Fraction &operator-=(FastInt64Fraction const &value)
		{
			*this += -value;
			return *this;
		}

		FastInt64Fraction &operator*=(FastInt64Fraction const &value)
		{
			base::Int128 num = _num;
			num *= value.Num();

			base::Int128 den = _den;
			den *= value.Den();

			ScaleFromInt128(num, den);
			return *this;
		}

		FastInt64Fraction &operator/=(FastInt64Fraction const &value)
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

		explicit operator int64_t() const
		{
			return Div();
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
			base::FastInt64Fraction copy{*this};
			copy.Simplify();

			double int_part = static_cast<double>(copy.Div());
			copy -= copy.Div();
			double fraction_part = static_cast<double>(copy.Num()) / static_cast<double>(copy.Den());
			return int_part + fraction_part;
		}

		explicit operator float() const
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
		/// @brief 本对象等于 other.
		/// @param other
		/// @return
		///
		bool operator==(FastInt64Fraction const &other) const
		{
			base::Int128 left = Num();
			left *= other.Den();

			base::Int128 right = other.Num();
			right *= Den();

			return left == right;
		}

		///
		/// @brief 本对象大于 other.
		/// @param other
		/// @return
		///
		bool operator>(FastInt64Fraction const &other) const
		{
			base::Int128 left = Num();
			left *= other.Den();

			base::Int128 right = other.Num();
			right *= Den();

			return left > right;
		}

		///
		/// @brief 本对象小于 other.
		/// @param other
		/// @return
		///
		bool operator<(FastInt64Fraction const &other) const
		{
			base::Int128 left = Num();
			left *= other.Den();

			base::Int128 right = other.Num();
			right *= Den();

			return left < right;
		}

		///
		/// @brief 本对象大于等于 other.
		///
		/// @param other
		///
		/// @return
		///
		bool operator>=(FastInt64Fraction const &other) const
		{
			base::Int128 left = Num();
			left *= other.Den();

			base::Int128 right = other.Num();
			right *= Den();

			return left >= right;
		}

		///
		/// @brief 本对象小于等于 other.
		///
		/// @param other
		///
		/// @return
		///
		bool operator<=(FastInt64Fraction const &other) const
		{
			base::Int128 left = Num();
			left *= other.Den();

			base::Int128 right = other.Num();
			right *= Den();

			return left <= right;
		}

		/* #endregion */

	}; // class FastInt64Fraction

	class FastInt64Fraction::Constant
	{
	public:
		///
		/// @brief 圆周率 Π.
		///
		/// @return
		///
		static base::FastInt64Fraction pi()
		{
			base::FastInt64Fraction ret{884279719003555, 281474976710656};
			return ret;
		}

		///
		/// @brief 欧拉常数 e, 或者叫自然常数，或者自然对数 ln 的底。
		///
		/// @return
		///
		static base::FastInt64Fraction e()
		{
			base::FastInt64Fraction ret{6121026514868073, 2251799813685248};
			return ret;
		}

		///
		/// @brief 水的比热容。
		///
		/// @note 4.187 kJ/(kg·K)
		///
		/// @return
		///
		static base::FastInt64Fraction specific_heat_capacity_of_water()
		{
			base::FastInt64Fraction ret{4187, 1000};
			return ret;
		}
	};

	/* #region 数学函数 */

	///
	/// @brief 取绝对值。
	///
	/// @param value
	/// @return
	///
	inline base::FastInt64Fraction abs(base::FastInt64Fraction const &value)
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
	inline int64_t floor(base::FastInt64Fraction const &value)
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
	inline int64_t ceil(base::FastInt64Fraction const &value)
	{
		return value.Ceil();
	}

	///
	/// @brief 降低分辨率。
	///
	/// @return 降低分辨率后的值。
	///
	inline base::FastInt64Fraction reduce_resolution(base::FastInt64Fraction const &value,
													 base::FastInt64Fraction const &resolution)
	{
		base::FastInt64Fraction copy = value;
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
