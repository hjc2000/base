#pragma once
#include "base/math/Fraction.h"
#include "IUnit.h"

namespace base::unit
{
	class J :
		public base::unit::IUnit<J>
	{
	private:
		base::Fraction _value;

	public:
		J() = default;

		template <typename T>
			requires(std::is_convertible_v<T, base::Fraction>)
		explicit J(T const &value)
		{
			_value = base::Fraction{value};
		}

		using base::unit::IUnit<J>::Value;

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
			return "J";
		}
	};

} // namespace base::unit
