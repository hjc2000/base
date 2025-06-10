#pragma once
#include "base/math/Pow.h"
#include "base/string/ICanToString.h"
#include "base/wrapper/number-wrapper.h"
#include "boost/multiprecision/cpp_int.hpp" // IWYU pragma: keep
#include <cstdint>
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
		boost::multiprecision::cpp_int _num = 0;
		boost::multiprecision::cpp_int _den = 1;

	public:
		/* #region 构造函数 */

		///
		/// @brief 默认构造，分子为 0，分母为 1.
		///
		Fraction() = default;

		///
		/// @brief 从整型值构造。分子为 num, 分母为 1.
		///
		/// @param num 分子。
		///
		template <typename T>
			requires(std::is_integral_v<T>)
		Fraction(T num)
		{
			_num = num;
			_den = 1;
		}

		///
		/// @brief 整型转化为分数，则分子等于整型，分母为 1.
		/// @param num
		///
		Fraction(boost::multiprecision::cpp_int num)
		{
			SetNum(num);
			SetDen(1);
		}

		///
		/// @brief 通过分子，分母进行构造。
		/// @param num 分子
		/// @param den 分母
		///
		Fraction(boost::multiprecision::cpp_int num, boost::multiprecision::cpp_int den)
		{
			SetNum(num);
			SetDen(den);
		}

		///
		/// @brief 通过浮点数构造。
		///
		/// @param value
		///
		Fraction(base::Double const &value)
		{
			double db = value.Value();
			int loop_times = 0;
			constexpr uint64_t factor = base::UIntPow(2, 63);
			while (db != 0)
			{
				boost::multiprecision::cpp_int int_part{static_cast<int64_t>(db)};
				base::Fraction temp{int_part, base::BigIntPow(factor, loop_times)};
				(*this) += temp;
				db -= static_cast<double>(int_part);
				db *= factor;
				++loop_times;
			}
		}

		/* #endregion */

		/* #region 分子分母 */

		///
		/// @brief 获取分子。
		///
		/// @return boost::multiprecision::cpp_int
		///
		boost::multiprecision::cpp_int Num() const
		{
			return _num;
		}

		///
		/// @brief 设置分子。
		///
		/// @param value
		///
		void SetNum(boost::multiprecision::cpp_int value)
		{
			_num = value;
		}

		///
		/// @brief 获取分母。
		///
		/// @return
		///
		boost::multiprecision::cpp_int Den() const
		{
			return _den;
		}

		///
		/// @brief 设置分母。
		///
		/// @param value
		///
		void SetDen(boost::multiprecision::cpp_int value)
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
		/// @brief 化简分数，返回化简后的值。
		/// @return
		///
		Fraction Simplify() const
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

		///
		/// @brief 倒数
		/// @return
		///
		Fraction Reciprocal() const
		{
			base::Fraction ret{_den, _num};
			return ret.Simplify();
		}

		///
		/// @brief 向下取整
		/// @return
		///
		boost::multiprecision::cpp_int Floor() const
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

		///
		/// @brief 向上取整
		/// @return
		///
		boost::multiprecision::cpp_int Ceil() const
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

		///
		/// @brief 获取分子除以分母的值
		/// @return
		///
		boost::multiprecision::cpp_int Div() const
		{
			return _num / _den;
		}

		///
		/// @brief 获取分子除以分母的余数
		/// @return
		///
		boost::multiprecision::cpp_int Mod() const
		{
			return _num % _den;
		}

		/* #endregion */

		Fraction operator-() const
		{
			Fraction ret{-_num, _den};
			return ret.Simplify();
		}

		/* #region 四则运算符 */

		Fraction operator+(Fraction const &value) const
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

		Fraction operator-(Fraction const &value) const
		{
			Fraction ret = *this + (-value);
			return ret.Simplify();
		}

		Fraction operator*(Fraction const &value) const
		{
			base::Fraction ret;
			ret.SetNum(_num * value.Num());
			ret.SetDen(_den * value.Den());
			return ret.Simplify();
		}

		Fraction operator/(Fraction const &value) const
		{
			Fraction ret{*this * value.Reciprocal()};
			return ret.Simplify();
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
		/// @return
		///
		virtual std::string ToString() const override;

		/* #region 强制转换运算符 */

		explicit operator boost::multiprecision::cpp_int() const
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
		bool operator==(Fraction const &another) const
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

		///
		/// @brief 本对象大于 another.
		/// @param another
		/// @return
		///
		bool operator>(Fraction const &another) const
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

		///
		/// @brief 本对象小于 another.
		/// @param another
		/// @return
		///
		bool operator<(Fraction const &another) const
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

		///
		/// @brief 本对象大于等于 another.
		///
		/// @param another
		/// @return true
		/// @return false
		///
		bool operator>=(Fraction const &another) const
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
		bool operator<=(Fraction const &another) const
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
		base::Fraction PI();

	} // namespace constant

} // namespace base

/* #region 全局四则运算符 */

///
/// @brief 加
///
/// @param left
/// @param right
/// @return base::Fraction
///
inline base::Fraction operator+(boost::multiprecision::cpp_int left, base::Fraction const &right)
{
	return base::Fraction{left} + right;
}

///
/// @brief 减
///
/// @param left
/// @param right
/// @return base::Fraction
///
inline base::Fraction operator-(boost::multiprecision::cpp_int left, base::Fraction const &right)
{
	return base::Fraction{left} - right;
}

///
/// @brief 乘
///
/// @param left
/// @param right
/// @return base::Fraction
///
inline base::Fraction operator*(boost::multiprecision::cpp_int left, base::Fraction const &right)
{
	return base::Fraction(left) * right;
}

///
/// @brief 除
///
/// @param left
/// @param right
/// @return base::Fraction
///
inline base::Fraction operator/(boost::multiprecision::cpp_int left, base::Fraction const &right)
{
	return base::Fraction{left} / right;
}

/* #endregion */

namespace std
{
	///
	/// @brief 向下取整
	/// @param value
	/// @return
	///
	inline boost::multiprecision::cpp_int floor(base::Fraction const &value)
	{
		return value.Floor();
	}

	///
	/// @brief 向上取整
	/// @param value
	/// @return
	///
	inline boost::multiprecision::cpp_int ceil(base::Fraction const &value)
	{
		return value.Ceil();
	}

	std::string to_string(boost::multiprecision::cpp_int const &value);

} // namespace std
