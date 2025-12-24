#pragma once
#include "base/math/Fraction.h"
#include "base/unit/A.h"
#include "base/unit/Hour.h"
#include "IUnit.h"
#include <type_traits>

namespace base::unit
{
	///
	/// @brief 安时。
	///
	class Ah :
		public base::unit::IUnit<Ah>
	{
	private:
		base::Fraction _value;

	public:
		Ah() = default;

		template <typename T>
			requires(std::is_convertible_v<T, base::Fraction>)
		explicit Ah(T const &value)
		{
			_value = base::Fraction{value};
		}

		using base::unit::IUnit<Ah>::Value;

		///
		/// @brief 单位的值。
		///
		/// @return
		///
		virtual base::Fraction &Value() override
		{
			return _value;
		}

		///
		/// @brief 单位的字符串。
		///
		/// @return
		///
		virtual std::string UnitString() const override
		{
			return "Ah";
		}
	};

} // namespace base::unit

/* #region 运算符重载 */

///
/// @brief 安 * 小时 = 安时
///
template <typename TLeft, typename TRight>
	requires(std::is_convertible_v<TLeft, base::unit::A> &&
			 std::is_convertible_v<TRight, base::unit::Hour>)
inline base::unit::Ah operator*(TLeft const &left, TRight const &right)
{
	base::Fraction a = base::unit::A{left}.Value();
	base::Fraction hour = base::unit::Hour{right}.Value();
	base::unit::Ah ret{a * hour};
	return ret;
}

///
/// @brief 安 * 小时 = 安时
///
template <typename TLeft, typename TRight>
	requires(std::is_convertible_v<TLeft, base::unit::Hour> &&
			 std::is_convertible_v<TRight, base::unit::A>)
inline base::unit::Ah operator*(TLeft const &left, TRight const &right)
{
	return right * left;
}

///
/// @brief 安时 / 安 = 小时
///
template <typename TLeft, typename TRight>
	requires(std::is_convertible_v<TLeft, base::unit::Ah> &&
			 std::is_convertible_v<TRight, base::unit::A>)
inline base::unit::Hour operator/(TLeft const &left, TRight const &right)
{
	base::Fraction ah = base::unit::Ah{left}.Value();
	base::Fraction a = base::unit::A{right}.Value();
	base::unit::Hour ret{ah / a};
	return ret;
}

///
/// @brief 安时 / 小时 = 安
///
template <typename TLeft, typename TRight>
	requires(std::is_convertible_v<TLeft, base::unit::Ah> &&
			 std::is_convertible_v<TRight, base::unit::Hour>)
inline base::unit::A operator/(TLeft const &left, TRight const &right)
{
	base::Fraction ah = base::unit::Ah{left}.Value();
	base::Fraction hour = base::unit::Hour{right}.Value();
	base::unit::A ret{ah / hour};
	return ret;
}

/* #endregion */
