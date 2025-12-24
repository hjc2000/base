#pragma once
#include "base/math/Fraction.h"
#include "base/unit/Hour.h"
#include "base/unit/mA.h"
#include "IUnit.h"
#include <type_traits>

namespace base::unit
{
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

template <typename TLeft, typename TRight>
	requires(std::is_convertible_v<TLeft, base::unit::Hour> &&
			 std::is_convertible_v<TRight, base::unit::mA>)
inline base::unit::mAh operator*(TLeft const &left, TRight const &right)
{
	return right * left;
}
