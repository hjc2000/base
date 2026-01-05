#pragma once
#include "A.h"
#include "base/math/Fraction.h"
#include "IUnit.h"
#include <type_traits>

namespace base::unit
{
	///
	/// @brief 电流单位：安培。
	///
	class mA :
		public base::unit::IUnit<mA>
	{
	private:
		base::Fraction _value;

	public:
		mA() = default;

		template <typename T>
			requires(std::is_convertible_v<T, base::Fraction>)
		explicit mA(T const &value)
		{
			_value = base::Fraction{value};
		}

		///
		/// @brief 从 A 构造。
		///
		/// @param value
		///
		mA(base::unit::A const &value)
		{
			_value = value.Value() * 1000;
		}

		///
		/// @brief 能转换到 A 的都从 A 构造。
		///
		template <typename T>
			requires(std::is_convertible_v<T, base::unit::A>)
		mA(T const &value)
			: mA{base::unit::A{value}}
		{
		}

		using base::unit::IUnit<mA>::Value;

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
			return "mA";
		}

		operator base::unit::A() const
		{
			base::unit::A ret{_value / 1000};
			return ret;
		}
	};

} // namespace base::unit
