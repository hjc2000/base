#pragma once
#include "base/math/Fraction.h"
#include "base/unit/Second.h"
#include "IUnit.h"
#include "W.h"
#include <type_traits>

namespace base::unit
{
	class J :
		public base::unit::IUnit<J>
	{
	private:
		base::Fraction _value;

	public:
		J() = default;

		template <typename T>
			requires(std::is_convertible_v<T, base::Fraction>)
		explicit J(T const &value)
		{
			_value = base::Fraction{value};
		}

		using base::unit::IUnit<J>::Value;

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
			return "J";
		}
	};

} // namespace base::unit

/* #region 运算符重载 */

///
/// @brief J = W * s
///
template <typename TLeft, typename TRight>
	requires(std::is_convertible_v<TLeft, base::unit::W> &&
			 std::is_convertible_v<TRight, base::unit::Second>)
inline base::unit::J operator*(TLeft const &left, TRight const &right)
{
	base::Fraction w = base::unit::W{left}.Value();
	base::Fraction s = base::unit::Second{right}.Value();
	base::unit::J ret{w * s};
	return ret;
}

///
/// @brief J = W * s
///
template <typename TLeft, typename TRight>
	requires(std::is_convertible_v<TLeft, base::unit::Second> &&
			 std::is_convertible_v<TRight, base::unit::W>)
inline base::unit::J operator*(TLeft const &left, TRight const &right)
{
	return right * left;
}

///
/// @brief W = J / s
///
template <typename TLeft, typename TRight>
	requires(std::is_convertible_v<TLeft, base::unit::J> &&
			 std::is_convertible_v<TRight, base::unit::Second>)
inline base::unit::W operator/(TLeft const &left, TRight const &right)
{
	base::Fraction j = base::unit::J{left}.Value();
	base::Fraction s = base::unit::Second{right}.Value();
	base::unit::W ret{j / s};
	return ret;
}

///
/// @brief s = J / W
///
template <typename TLeft, typename TRight>
	requires(std::is_convertible_v<TLeft, base::unit::J> &&
			 std::is_convertible_v<TRight, base::unit::W>)
inline base::unit::Second operator/(TLeft const &left, TRight const &right)
{
	base::Fraction j = base::unit::J{left}.Value();
	base::Fraction w = base::unit::W{right}.Value();
	base::unit::Second ret{j / w};
	return ret;
}

/* #endregion */
