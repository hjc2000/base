#pragma once
#include "base/math/Fraction.h"
#include "IUnit.h"
#include <cstdint>

namespace base
{
	class W;
	class kW;

	class kW :
		public base::IUnit<kW>
	{
	private:
		base::Fraction _value;

	public:
		kW() = default;

		kW(int64_t value)
		{
			_value = value;
		}

		kW(base::Fraction const &value)
		{
			_value = value;
		}

		kW(base::W const &value);

		using base::IUnit<kW>::Value;

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
