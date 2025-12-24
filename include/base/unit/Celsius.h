#pragma once
#include "base/math/Fraction.h"
#include "base/unit/IUnit.h"
#include "IUnit.h"
#include <type_traits>

namespace base::unit
{
	///
	/// @brief 温度单位。摄氏度 ℃.
	///
	class Celsius :
		public base::unit::IUnit<Celsius>
	{
	private:
		base::Fraction _value;

	public:
		Celsius() = default;

		template <typename T>
			requires(std::is_convertible_v<T, base::Fraction>)
		explicit Celsius(T const &value)
		{
			_value = base::Fraction{value};
		}

		using base::unit::IUnit<Celsius>::Value;

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
			return "℃";
		}
	};

} // namespace base::unit
