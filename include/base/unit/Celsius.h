#pragma once
#include "base/math/Fraction.h"
#include "base/unit/IUnit.h"

namespace base::unit
{
	///
	/// @brief 温度单位。摄氏度 ℃.
	///
	///
	class Celsius :
		public base::unit::IUnit<Celsius>
	{
	private:
		base::Fraction _value;

	public:
		Celsius() = default;

		template <typename value_type>
			requires(std::is_integral_v<value_type>)
		explicit Celsius(value_type value)
		{
			_value = value;
		}

		explicit Celsius(base::Fraction const &value)
		{
			_value = value;
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
