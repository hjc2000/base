#pragma once
#include "base/math/Fraction.h"
#include "base/unit/IUnit.h"
#include <cstdint>

namespace base
{
	///
	/// @brief 温度单位。摄氏度 ℃.
	///
	///
	class Celsius :
		public base::IUnit<Celsius>
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

		Celsius(base::Fraction const &value)
		{
			_value = value;
		}

		using base::IUnit<Celsius>::Value;

		///
		/// @brief 单位的值。
		///
		/// @return base::Fraction&
		///
		virtual base::Fraction &Value() override;

		///
		/// @brief 单位的字符串。
		///
		/// @return std::string
		///
		virtual std::string UnitString() const override;
	};
} // namespace base
