#pragma once
#include "base/math/Fraction.h"
#include "IUnit.h"
#include <type_traits>

namespace base::unit
{
	///
	/// @brief 电压单位：伏特。
	///
	class V :
		public base::unit::IUnit<V>
	{
	private:
		base::Fraction _value;

	public:
		V() = default;

		template <typename T>
			requires(std::is_convertible_v<T, base::Fraction>)
		explicit V(T const &value)
		{
			_value = base::Fraction{value};
		}

		using base::unit::IUnit<V>::Value;

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
			return "V";
		}
	};

} // namespace base::unit
