#pragma once
#include "base/math/Fraction.h"
#include "base/unit/IUnit.h"

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
