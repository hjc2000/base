#pragma once
#include "base/math/Fraction.h"
#include "IUnit.h"
#include <cstdint>

namespace base
{
	///
	/// @brief 电压单位：伏特。
	///
	///
	class V :
		public base::IUnit<V>
	{
	private:
		base::Fraction _value;

	public:
		V() = default;

		V(int64_t value)
		{
			_value = value;
		}

		V(base::Fraction const &value)
		{
			_value = value;
		}

		using base::IUnit<V>::Value;

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
