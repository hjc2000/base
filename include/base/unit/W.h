#pragma once
#include "A.h"
#include "base/math/Fraction.h"
#include "IUnit.h"
#include "V.h"

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

		template <typename value_type>
			requires(std::is_integral_v<value_type>)
		explicit W(value_type value)
		{
			_value = value;
		}

		explicit W(base::Fraction const &value)
		{
			_value = value;
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

		base::unit::V operator/(base::unit::A const &rhs) const
		{
			base::unit::V ret{_value / rhs.Value()};
			return ret;
		}

		base::unit::A operator/(base::unit::V const &rhs) const
		{
			base::unit::A ret{_value / rhs.Value()};
			return ret;
		}
	};

} // namespace base::unit

template <typename TLeft, typename TRight>
	requires(std::is_convertible_v<TLeft, base::unit::V> &&
			 std::is_convertible_v<TRight, base::unit::A>)
inline base::unit::W operator*(TLeft const &lhs, TRight const &rhs)
{
	base::unit::W ret{base::unit::V{lhs}.Value() * base::unit::A{rhs}.Value()};
	return ret;
}

template <typename TLeft, typename TRight>
	requires(std::is_convertible_v<TLeft, base::unit::A> &&
			 std::is_convertible_v<TRight, base::unit::V>)
inline base::unit::W operator*(TLeft const &lhs, TRight const &rhs)
{
	return rhs * lhs;
}
