#pragma once
#include "base/math/math.h"
#include "base/string/ICanToString.h"
#include "base/wrapper/number-wrapper.h"
#include <cstdint>
#include <numeric>
#include <stdexcept>
#include <string>

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
		constexpr Int64Fraction(T num)
		{
			_num = num;
			_den = 1;
		}

		///
		/// @brief 通过分子，分母进行构造。
		/// @param num 分子
		/// @param den 分母
		///
		constexpr Int64Fraction(int64_t num, int64_t den)
		{
			SetNum(num);
			if (num == 0)
			{
				SetDen(1);
			}
			else
			{
				SetDen(den);
			}
		}

		///
		/// @brief 通过浮点数构造。
		///
		/// @param value
		///
		constexpr Int64Fraction(base::Double const &value)
		{
			if (value.Value() == 0.0)
			{
				SetNum(0);
				SetDen(1);
				return;
			}

			double db = value.Value();

			// 要保证分数计算过程不溢出，需要保证 factor * db <= INT64_MAX.
			int64_t factor = INT64_MAX / base::ceil(db);

			base::Int64Fraction int_part{static_cast<int64_t>(db)};
			db -= static_cast<double>(int_part);

			db *= factor;
			base::Int64Fraction fractional_part{static_cast<int64_t>(db), factor};

			*this += int_part + fractional_part;
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
		/// @brief 设置分子。
		///
		/// @param value
		///
		constexpr void SetNum(int64_t value)
		{
			_num = value;
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

		///
		/// @brief 设置分母。
		///
		/// @param value
		///
		constexpr void SetDen(int64_t value)
		{
			if (value == 0)
			{
				throw std::invalid_argument{"分母不能为 0."};
			}

			_den = value;
		}

		/* #endregion */

		/* #region 计算函数 */

		///
		/// @brief 化简自身。
		///
		///
		constexpr void Simplify()
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
			int64_t gcd_value = std::gcd(_num, _den);
			int64_t scaled_num = _num / gcd_value;
			int64_t scaled_den = _den / gcd_value;

			if (scaled_den < 0)
			{
				// 如果分母小于 0，分子分母同时取相反数
				scaled_num = -scaled_num;
				scaled_den = -scaled_den;
			}

			_num = scaled_num;
			_den = scaled_den;
		}

		///
		/// @brief 化简后的形式。
		///
		/// @note 返回化简后的值，不改变自身。
		///
		/// @return
		///
		constexpr Int64Fraction SimplifiedForm() const
		{
			base::Int64Fraction ret{*this};
			ret.Simplify();
			return ret;
		}

		///
		/// @brief 倒数
		/// @return
		///
		constexpr Int64Fraction Reciprocal() const
		{
			base::Int64Fraction ret{_den, _num};
			return ret.SimplifiedForm();
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

		/* #endregion */

		constexpr Int64Fraction operator-() const
		{
			Int64Fraction ret{-_num, _den};
			return ret.SimplifiedForm();
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

			return ret.SimplifiedForm();
		}

		constexpr Int64Fraction operator-(Int64Fraction const &value) const
		{
			Int64Fraction ret = *this + (-value);
			return ret.SimplifiedForm();
		}

		constexpr Int64Fraction operator*(Int64Fraction const &value) const
		{
			base::Int64Fraction ret;
			ret.SetNum(_num * value.Num());
			ret.SetDen(_den * value.Den());
			return ret.SimplifiedForm();
		}

		constexpr Int64Fraction operator/(Int64Fraction const &value) const
		{
			Int64Fraction ret{*this * value.Reciprocal()};
			return ret.SimplifiedForm();
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
				/* 2 个分子都为 0 直接返回相等，这样更加安全，避免分子都为 0
				 * 分母不相等时错误地将两个分数判断为不相等。
				 */
				return true;
			}

			Int64Fraction f1 = SimplifiedForm();
			Int64Fraction f2 = another.SimplifiedForm();
			return f1.Num() == f2.Num() && f1.Den() == f2.Den();
		}

		///
		/// @brief 本对象大于 another.
		/// @param another
		/// @return
		///
		constexpr bool operator>(Int64Fraction const &another) const
		{
			// 先化简，避免分母为负数，然后使用交叉乘法比大小。
			Int64Fraction f1 = SimplifiedForm();
			Int64Fraction f2 = another.SimplifiedForm();
			int64_t num1{f1.Num()};
			int64_t den1{f1.Den()};
			int64_t num2{f2.Num()};
			int64_t den2{f2.Den()};
			return num1 * den2 > num2 * den1;
		}

		///
		/// @brief 本对象小于 another.
		/// @param another
		/// @return
		///
		constexpr bool operator<(Int64Fraction const &another) const
		{
			// 先化简，避免分母为负数，然后使用交叉乘法比大小。
			Int64Fraction f1 = SimplifiedForm();
			Int64Fraction f2 = another.SimplifiedForm();
			int64_t num1{f1.Num()};
			int64_t den1{f1.Den()};
			int64_t num2{f2.Num()};
			int64_t den2{f2.Den()};
			return num1 * den2 < num2 * den1;
		}

		///
		/// @brief 本对象大于等于 another.
		///
		/// @param another
		/// @return true
		/// @return false
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
		/// @return true
		/// @return false
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
		constexpr base::Int64Fraction pi{base::Double{std::numbers::pi}};

		///
		/// @brief 自然对数 ln 的底。
		///
		///
		constexpr base::Int64Fraction e{base::Double{std::numbers::e}};

	} // namespace constant
} // namespace base

/* #region 全局四则运算符 */

///
/// @brief 加
///
/// @param left
/// @param right
/// @return base::Int64Fraction
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
/// @return base::Int64Fraction
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
/// @return base::Int64Fraction
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
/// @return base::Int64Fraction
///
inline base::Int64Fraction operator/(int64_t left, base::Int64Fraction const &right)
{
	return base::Int64Fraction{left} / right;
}

/* #endregion */

namespace std
{
	///
	/// @brief 取绝对值。
	///
	/// @param value
	/// @return
	///
	inline base::Int64Fraction abs(base::Int64Fraction const &value)
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
	inline int64_t floor(base::Int64Fraction const &value)
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
	inline int64_t ceil(base::Int64Fraction const &value)
	{
		return value.Ceil();
	}

} // namespace std
