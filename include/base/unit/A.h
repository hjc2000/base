#pragma once
#include "base/math/Fraction.h"
#include "IUnit.h"

namespace base
{
	class A :
		public base::IUnit<A>
	{
	private:
		base::Fraction _value;

	public:
		using base::IUnit<A>::Value;

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
