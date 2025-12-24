#pragma once
#include "base/math/Fraction.h"
#include "base/unit/Hour.h"
#include "base/unit/J.h"
#include "base/unit/mAh.h"
#include "base/unit/mW.h"
#include "base/unit/V.h"
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

		mWh(base::unit::J const &value)
		{
			// mWh
			// = mW * Hour
			// = W / 1000 * Hour
			// = W * Hour / 1000
			// = W * s * 3600 / 1000
			// = J * 3600 / 1000
			//
			// 反过来
			// J = mWh / 3600 * 1000
			_value = value.Value() / 3600 * 1000;
		}

		template <typename T>
			requires(std::is_convertible_v<T, base::unit::J>)
		mWh(T const &value)
			: mWh{base::unit::J{value}}
		{
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

		operator base::unit::J() const
		{
			// mWh
			// = mW * Hour
			// = W / 1000 * Hour
			// = W * Hour / 1000
			// = W * s * 3600 / 1000
			// = J * 3600 / 1000
			//
			// 反过来
			// J = mWh / 3600 * 1000
			base::unit::J ret{_value * 3600 / 1000};
			return ret;
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

/* #region mWh = mAh * V 运算符重载 */

template <typename TLeft, typename TRight>
	requires(std::is_convertible_v<TLeft, base::unit::mAh> &&
			 std::is_convertible_v<TRight, base::unit::V>)
inline base::unit::mWh operator*(TLeft const &left, TRight const &right)
{
	base::Fraction mah = base::unit::mAh{left}.Value();
	base::Fraction v = base::unit::V{right}.Value();
	base::unit::mWh ret{mah * v};
	return ret;
}

template <typename TLeft, typename TRight>
	requires(std::is_convertible_v<TLeft, base::unit::V> &&
			 std::is_convertible_v<TRight, base::unit::mAh>)
inline base::unit::mWh operator*(TLeft const &left, TRight const &right)
{
	return right * left;
}

template <typename TLeft, typename TRight>
	requires(std::is_convertible_v<TLeft, base::unit::mWh> &&
			 std::is_convertible_v<TRight, base::unit::V>)
inline base::unit::mAh operator*(TLeft const &left, TRight const &right)
{
	base::Fraction mwh = base::unit::mWh{left}.Value();
	base::Fraction v = base::unit::V{right}.Value();
	base::unit::mAh ret{mwh / v};
	return ret;
}

template <typename TLeft, typename TRight>
	requires(std::is_convertible_v<TLeft, base::unit::mWh> &&
			 std::is_convertible_v<TRight, base::unit::mAh>)
inline base::unit::V operator/(TLeft const &left, TRight const &right)
{
	base::Fraction mwh = base::unit::mWh{left}.Value();
	base::Fraction mah = base::unit::mAh{right}.Value();
	base::unit::V ret{mwh / mah};
	return ret;
}

/* #endregion */
