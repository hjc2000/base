#pragma once
#include "base/math/Fraction.h"
#include "base/unit/Hour.h"
#include "base/unit/mA.h"
#include "IUnit.h"
#include <type_traits>

namespace base::unit
{
	///
	/// @brief 毫安时。
	///
	class mAh :
		public base::unit::IUnit<mAh>
	{
	private:
		base::Fraction _value;

	public:
		mAh() = default;

		template <typename T>
			requires(std::is_convertible_v<T, base::Fraction>)
		explicit mAh(T const &value)
		{
			_value = base::Fraction{value};
		}

		using base::unit::IUnit<mAh>::Value;

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
			return "mAh";
		}
	};

} // namespace base::unit

/* #region mAh = mA * Hour 运算符重载 */

///
/// @brief 毫安 * 小时 = 毫安时
///
template <typename TLeft, typename TRight>
	requires(std::is_convertible_v<TLeft, base::unit::mA> &&
			 std::is_convertible_v<TRight, base::unit::Hour>)
inline base::unit::mAh operator*(TLeft const &left, TRight const &right)
{
	base::Fraction ma = base::unit::mA{left}.Value();
	base::Fraction hour = base::unit::Hour{right}.Value();
	base::unit::mAh ret{ma * hour};
	return ret;
}

///
/// @brief 毫安 * 小时 = 毫安时
///
template <typename TLeft, typename TRight>
	requires(std::is_convertible_v<TLeft, base::unit::Hour> &&
			 std::is_convertible_v<TRight, base::unit::mA>)
inline base::unit::mAh operator*(TLeft const &left, TRight const &right)
{
	return right * left;
}

///
/// @brief 毫安时 / 毫安 = 小时
///
template <typename TLeft, typename TRight>
	requires(std::is_convertible_v<TLeft, base::unit::mAh> &&
			 std::is_convertible_v<TRight, base::unit::mA>)
inline base::unit::Hour operator/(TLeft const &left, TRight const &right)
{
	base::Fraction mah = base::unit::mAh{left}.Value();
	base::Fraction ma = base::unit::mA{right}.Value();
	base::unit::Hour ret{mah / ma};
	return ret;
}

///
/// @brief 毫安时 / 小时 = 毫安
///
template <typename TLeft, typename TRight>
	requires(std::is_convertible_v<TLeft, base::unit::mAh> &&
			 std::is_convertible_v<TRight, base::unit::Hour>)
inline base::unit::mA operator/(TLeft const &left, TRight const &right)
{
	base::Fraction mah = base::unit::mAh{left}.Value();
	base::Fraction hour = base::unit::Hour{right}.Value();
	base::unit::mA ret{mah / hour};
	return ret;
}

/* #endregion */
