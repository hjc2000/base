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
			// 单位转换方法
			// https://blog.csdn.net/qq_36148047/article/details/156243911?sharetype=blogdetail&sharerId=156243911&sharerefer=PC&sharesource=qq_36148047&spm=1011.2480.3001.8118
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
			// 单位转换方法
			// https://blog.csdn.net/qq_36148047/article/details/156243911?sharetype=blogdetail&sharerId=156243911&sharerefer=PC&sharesource=qq_36148047&spm=1011.2480.3001.8118
			base::unit::Celsius ret{(_value - 32) * 5 / 9};
			return ret;
		}
	};

} // namespace base::unit
