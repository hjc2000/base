#pragma once
#include "base/math/Fraction.h"
#include "base/unit/Hour.h"
#include "base/unit/mW.h"
#include "IUnit.h"
#include <type_traits>

namespace base::unit
{
	///
	/// @brief 毫安时。
	///
	class mWh :
		public base::unit::IUnit<mWh>
	{
	private:
		base::Fraction _value;

	public:
		mWh() = default;

		template <typename T>
			requires(std::is_convertible_v<T, base::Fraction>)
		explicit mWh(T const &value)
		{
			_value = base::Fraction{value};
		}

		using base::unit::IUnit<mWh>::Value;

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
			return "mWh";
		}
	};

} // namespace base::unit

/* #region mWh = mW * Hour 运算符重载 */

template <typename TLeft, typename TRight>
	requires(std::is_convertible_v<TLeft, base::unit::mW> &&
			 std::is_convertible_v<TRight, base::unit::Hour>)
inline base::unit::mWh operator*(TLeft const &left, TRight const &right)
{
	base::Fraction mw = base::unit::mW{left}.Value();
	base::Fraction hour = base::unit::Hour{right}.Value();
	base::unit::mWh ret{mw * hour};
	return ret;
}

template <typename TLeft, typename TRight>
	requires(std::is_convertible_v<TLeft, base::unit::Hour> &&
			 std::is_convertible_v<TRight, base::unit::mW>)
inline base::unit::mWh operator*(TLeft const &left, TRight const &right)
{
	return right * left;
}

template <typename TLeft, typename TRight>
	requires(std::is_convertible_v<TLeft, base::unit::mWh> &&
			 std::is_convertible_v<TRight, base::unit::mW>)
base::unit::Hour operator/(TLeft const &left, TRight const &right)
{
	base::Fraction mwh = base::unit::mWh{left}.Value();
	base::Fraction mw = base::unit::mW{right}.Value();
	base::unit::Hour ret{mwh / mw};
	return ret;
}

template <typename TLeft, typename TRight>
	requires(std::is_convertible_v<TLeft, base::unit::mWh> &&
			 std::is_convertible_v<TRight, base::unit::Hour>)
base::unit::mW operator/(TLeft const &left, TRight const &right)
{
	base::Fraction mwh = base::unit::mWh{left}.Value();
	base::Fraction hour = base::unit::Hour{right}.Value();
	base::unit::mW ret{mwh / hour};
	return ret;
}

/* #endregion */
