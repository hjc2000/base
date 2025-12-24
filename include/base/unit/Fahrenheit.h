#pragma once
#include "base/math/Fraction.h"
#include "base/unit/IUnit.h"
#include "Celsius.h"
#include "IUnit.h"
#include <type_traits>

namespace base::unit
{
	///
	/// @brief 温度单位。华氏度 ℉.
	///
	class Fahrenheit :
		public base::unit::IUnit<Fahrenheit>
	{
	private:
		base::Fraction _value;

	public:
		Fahrenheit() = default;

		template <typename T>
			requires(std::is_convertible_v<T, base::Fraction>)
		explicit Fahrenheit(T const &value)
		{
			_value = base::Fraction{value};
		}

		Fahrenheit(base::unit::Celsius const &value)
		{
			// 华氏度和摄氏度转换的公式为：
			// F = C * 9 / 5 + 32
			// 数字 C 的单位是 ℃
			// 数字 F 的单位是 ℉
			//
			// 按照增量的当量来计算，
			// ℃ = ℉ * (9 / 5)
			//
			// 然后华氏度的零点比摄氏度的零点高，高了 32℉，
			// 所以换算完的结果要再加上 32℉.
			_value = value.Value() * 9 / 5 + 32;
		}

		template <typename T>
			requires(std::is_convertible_v<T, base::unit::Celsius>)
		Fahrenheit(T const &value)
			: Fahrenheit{base::unit::Celsius{value}}
		{
		}

		using base::unit::IUnit<Fahrenheit>::Value;

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
			return "℉";
		}

		operator base::unit::Celsius() const
		{
			// F = C * 9 / 5 + 32
			// 数字 C 的单位是 ℃
			// 数字 F 的单位是 ℉
			//
			// C = (F - 32) * 5 / 9
			base::unit::Celsius ret{(_value - 32) * 5 / 9};
			return ret;
		}
	};

} // namespace base::unit
