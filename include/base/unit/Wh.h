#pragma once
#include "base/math/Fraction.h"
#include "base/unit/Ah.h"
#include "base/unit/J.h"
#include "IUnit.h"
#include <type_traits>

namespace base::unit
{
	///
	/// @brief 瓦时
	///
	class Wh :
		public base::unit::IUnit<Wh>
	{
	private:
		base::Fraction _value;

	public:
		Wh() = default;

		template <typename T>
			requires(std::is_convertible_v<T, base::Fraction>)
		explicit Wh(T const &value)
		{
			_value = base::Fraction{value};
		}

		Wh(base::unit::J const &value)
		{
			// Wh = W * s * 3600
			// = J * 3600
			//
			// 反过来
			// J = Wh / 3600
			_value = value.Value() / 3600;
		}

		template <typename T>
			requires(std::is_convertible_v<T, base::unit::J>)
		Wh(T const &value)
			: Wh{base::unit::J{value}}
		{
		}

		using base::unit::IUnit<Wh>::Value;

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
			return "Wh";
		}

		operator base::unit::J() const
		{
			// Wh = W * s * 3600
			// = J * 3600
			//
			// 反过来
			// J = Wh / 3600
			base::unit::J ret{_value * 3600};
			return ret;
		}
	};

} // namespace base::unit

/* #region 运算符重载 */

///
/// @brief Wh = Ah * V
///
template <typename TLeft, typename TRight>
	requires(std::is_convertible_v<TLeft, base::unit::Ah> &&
			 std::is_convertible_v<TRight, base::unit::V>)
inline base::unit::Wh operator*(TLeft const &left, TRight const &right)
{
	base::Fraction ah = base::unit::Ah{left}.Value();
	base::Fraction v = base::unit::V{right}.Value();
	base::unit::Wh ret{ah * v};
	return ret;
}

///
/// @brief Wh = Ah * V
///
template <typename TLeft, typename TRight>
	requires(std::is_convertible_v<TLeft, base::unit::V> &&
			 std::is_convertible_v<TRight, base::unit::Ah>)
inline base::unit::Wh operator*(TLeft const &left, TRight const &right)
{
	return right * left;
}

///
/// @brief Ah = Wh / V
///
template <typename TLeft, typename TRight>
	requires(std::is_convertible_v<TLeft, base::unit::Wh> &&
			 std::is_convertible_v<TRight, base::unit::V>)
inline base::unit::Ah operator*(TLeft const &left, TRight const &right)
{
	base::Fraction wh = base::unit::Wh{left}.Value();
	base::Fraction v = base::unit::V{right}.Value();
	base::unit::Ah ret{wh / v};
	return ret;
}

///
/// @brief V = Wh / Ah
///
template <typename TLeft, typename TRight>
	requires(std::is_convertible_v<TLeft, base::unit::Wh> &&
			 std::is_convertible_v<TRight, base::unit::Ah>)
inline base::unit::V operator/(TLeft const &left, TRight const &right)
{
	base::Fraction wh = base::unit::Wh{left}.Value();
	base::Fraction ah = base::unit::Ah{right}.Value();
	base::unit::V ret{wh / ah};
	return ret;
}

/* #endregion */
