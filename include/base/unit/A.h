#pragma once
#include "base/math/Fraction.h"
#include "IUnit.h"
#include <cstdint>

namespace base
{
	///
	/// @brief 电流单位：安培。
	///
	///
	class A :
		public base::IUnit<A>
	{
	private:
		base::Fraction _value;

	public:
		A() = default;
		A(int64_t value);
		A(base::Fraction const &value);

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
