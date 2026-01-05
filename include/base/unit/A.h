#pragma once
#include "base/math/Fraction.h"
#include "IUnit.h"
#include <type_traits>

namespace base::unit
{
	///
	/// @brief 电流单位：安培。
	///
	class A :
		public base::unit::IUnit<A>
	{
	private:
		base::Fraction _value;

	public:
		A() = default;

		template <typename T>
			requires(std::is_convertible_v<T, base::Fraction>)
		explicit A(T const &value)
		{
			_value = base::Fraction{value};
		}

		using base::unit::IUnit<A>::Value;

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
			return "A";
		}
	};

} // namespace base::unit
