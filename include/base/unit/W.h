#pragma once
#include "A.h"
#include "base/math/Fraction.h"
#include "IUnit.h"
#include "V.h"
#include <type_traits>

namespace base::unit
{
	///
	/// @brief 功率单位：瓦。
	///
	class W :
		public base::unit::IUnit<W>
	{
	private:
		base::Fraction _value;

	public:
		W() = default;

		template <typename T>
			requires(std::is_convertible_v<T, base::Fraction>)
		explicit W(T const &value)
		{
			_value = base::Fraction{value};
		}

		using base::unit::IUnit<W>::Value;

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
			return "W";
		}
	};

} // namespace base::unit

/* #region W = V * A 运算符重载 */

///
/// @brief W = V * A
///
template <typename TLeft, typename TRight>
	requires(std::is_convertible_v<TLeft, base::unit::V> &&
			 std::is_convertible_v<TRight, base::unit::A>)
inline base::unit::W operator*(TLeft const &left, TRight const &right)
{
	base::Fraction v = base::unit::V{left}.Value();
	base::Fraction a = base::unit::A{right}.Value();
	base::unit::W ret{v * a};
	return ret;
}

///
/// @brief W = V * A
///
template <typename TLeft, typename TRight>
	requires(std::is_convertible_v<TLeft, base::unit::A> &&
			 std::is_convertible_v<TRight, base::unit::V>)
inline base::unit::W operator*(TLeft const &left, TRight const &right)
{
	return right * left;
}

///
/// @brief V = W / A
///
template <typename TLeft, typename TRight>
	requires(std::is_convertible_v<TLeft, base::unit::W> &&
			 std::is_convertible_v<TRight, base::unit::A>)
base::unit::V operator/(TLeft const &left, TRight const &right)
{
	base::Fraction w = base::unit::W{left}.Value();
	base::Fraction a = base::unit::A{right}.Value();
	base::unit::V ret{w / a};
	return ret;
}

///
/// @brief A = W / V
///
template <typename TLeft, typename TRight>
	requires(std::is_convertible_v<TLeft, base::unit::W> &&
			 std::is_convertible_v<TRight, base::unit::V>)
base::unit::A operator/(TLeft const &left, TRight const &right)
{
	base::Fraction w = base::unit::W{left}.Value();
	base::Fraction v = base::unit::V{right}.Value();
	base::unit::A ret{w / v};
	return ret;
}

/* #endregion */
