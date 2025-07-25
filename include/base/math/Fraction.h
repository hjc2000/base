#pragma once
#include "base/math/BigInteger.h"
#include "base/string/ICanToString.h"
#include "base/wrapper/number-wrapper.h"
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
		base::BigInteger _num = 0;
		base::BigInteger _den = 1;

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
		Fraction(base::BigInteger num)
		{
			SetNum(num);
			SetDen(1);
		}

		///
		/// @brief 通过分子，分母进行构造。
		/// @param num 分子
		/// @param den 分母
		///
		Fraction(base::BigInteger num, base::BigInteger den)
		{
			SetNum(num);
			if (num == 0)
			{
				SetDen(1);
			}
			else
			{
				SetDen(den);
				Simplify();
			}
		}

		///
		/// @brief 通过浮点数构造。
		///
		/// @param value
		///
		Fraction(base::Double const &value);

		/* #endregion */

		/* #region 分子分母 */

		///
		/// @brief 获取分子。
		///
		/// @return base::BigInteger
		///
		base::BigInteger Num() const
		{
			return _num;
		}

		///
		/// @brief 设置分子。
		///
		/// @param value
		///
		void SetNum(base::BigInteger value)
		{
			_num = value;
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

		///
		/// @brief 设置分母。
		///
		/// @param value
		///
		void SetDen(base::BigInteger value)
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
		void Simplify();

		///
		/// @brief 化简后的形式。
		///
		/// @note 返回化简后的值，不改变自身。
		///
		/// @return
		///
		Fraction SimplifiedForm() const
		{
			base::Fraction ret{*this};
			ret.Simplify();
			return ret;
		}

		///
		/// @brief 倒数
		/// @return
		///
		Fraction Reciprocal() const
		{
			base::Fraction ret{_den, _num};
			return ret.SimplifiedForm();
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
		/// @return
		///
		base::BigInteger Div() const
		{
			return _num / _den;
		}

		///
		/// @brief 获取分子除以分母的余数
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
		void ReduceResolution(base::Fraction const &resolution);

		/* #endregion */

		Fraction operator-() const
		{
			Fraction ret{-_num, _den};
			return ret.SimplifiedForm();
		}

		/* #region 四则运算符 */

		Fraction operator+(Fraction const &value) const;

		Fraction operator-(Fraction const &value) const;

		Fraction operator*(Fraction const &value) const;

		Fraction operator/(Fraction const &value) const;

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

		explicit operator double() const;

		/* #endregion */

		/* #region 比较 */

		///
		/// @brief 本对象等于 another.
		/// @param another
		/// @return
		///
		bool operator==(Fraction const &another) const;

		///
		/// @brief 本对象大于 another.
		/// @param another
		/// @return
		///
		bool operator>(Fraction const &another) const;

		///
		/// @brief 本对象小于 another.
		/// @param another
		/// @return
		///
		bool operator<(Fraction const &another) const;

		///
		/// @brief 本对象大于等于 another.
		///
		/// @param another
		/// @return true
		/// @return false
		///
		bool operator>=(Fraction const &another) const;

		///
		/// @brief 本对象小于等于 another.
		///
		/// @param another
		/// @return true
		/// @return false
		///
		bool operator<=(Fraction const &another) const;

		/* #endregion */
	};

	///
	/// @brief 取绝对值。
	///
	/// @param value
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

} // namespace base

/* #region 全局四则运算符 */

///
/// @brief 加
///
/// @param left
/// @param right
/// @return base::Fraction
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
/// @return base::Fraction
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
/// @return base::Fraction
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
/// @return base::Fraction
///
inline base::Fraction operator/(base::BigInteger left, base::Fraction const &right)
{
	return base::Fraction{left} / right;
}

/* #endregion */
