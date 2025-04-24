#pragma once
#include "base/string/ICanToString.h"
#include "base/wrapper/number-wrapper.h"
#include "boost/multiprecision/cpp_int.hpp" // IWYU pragma: keep
#include <stdint.h>
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
		Fraction(boost::multiprecision::cpp_int num);

		///
		/// @brief 通过分子，分母进行构造。
		/// @param num 分子
		/// @param den 分母
		///
		Fraction(boost::multiprecision::cpp_int num, boost::multiprecision::cpp_int den);

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
		/// @return boost::multiprecision::cpp_int
		///
		boost::multiprecision::cpp_int Num() const;

		///
		/// @brief 设置分子。
		///
		/// @param value
		///
		void SetNum(boost::multiprecision::cpp_int value);

		///
		/// @brief 获取分母。
		///
		/// @return boost::multiprecision::cpp_int
		///
		boost::multiprecision::cpp_int Den() const;

		///
		/// @brief 设置分母。
		///
		/// @param value
		///
		void SetDen(boost::multiprecision::cpp_int value);

		/* #endregion */

		/* #region 计算函数 */

		///
		/// @brief 化简分数，返回化简后的值。
		/// @return
		///
		Fraction Simplify() const;

		///
		/// @brief 倒数
		/// @return
		///
		Fraction Reciprocal() const;

		///
		/// @brief 向下取整
		/// @return
		///
		boost::multiprecision::cpp_int Floor() const;

		///
		/// @brief 向上取整
		/// @return
		///
		boost::multiprecision::cpp_int Ceil() const;

		///
		/// @brief 获取分子除以分母的值
		/// @return
		///
		boost::multiprecision::cpp_int Div() const;

		///
		/// @brief 获取分子除以分母的余数
		/// @return
		///
		boost::multiprecision::cpp_int Mod() const;

		/* #endregion */

		/* #region 四则运算 */

		Fraction operator-() const;
		Fraction operator+(Fraction const &value) const;
		Fraction operator-(Fraction const &value) const;
		Fraction operator*(Fraction const &value) const;
		Fraction operator/(Fraction const &value) const;

		Fraction &operator+=(Fraction const &value);
		Fraction &operator-=(Fraction const &value);
		Fraction &operator*=(Fraction const &value);
		Fraction &operator/=(Fraction const &value);

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

	namespace constant
	{
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
base::Fraction operator+(boost::multiprecision::cpp_int left, base::Fraction const &right);

///
/// @brief 减
///
/// @param left
/// @param right
/// @return base::Fraction
///
base::Fraction operator-(boost::multiprecision::cpp_int left, base::Fraction const &right);

///
/// @brief 乘
///
/// @param left
/// @param right
/// @return base::Fraction
///
base::Fraction operator*(boost::multiprecision::cpp_int left, base::Fraction const &right);

///
/// @brief 除
///
/// @param left
/// @param right
/// @return base::Fraction
///
base::Fraction operator/(boost::multiprecision::cpp_int left, base::Fraction const &right);

/* #endregion */

namespace std
{
	///
	/// @brief 向下取整
	/// @param value
	/// @return
	///
	boost::multiprecision::cpp_int floor(base::Fraction const &value);

	///
	/// @brief 向上取整
	/// @param value
	/// @return
	///
	boost::multiprecision::cpp_int ceil(base::Fraction const &value);

	std::string to_string(boost::multiprecision::cpp_int const &value);

} // namespace std
