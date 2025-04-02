#pragma once
#include "base/math/Fraction.h"
#include "base/unit/IUnit.h"
#include <cstdint>

namespace base
{
	///
	/// @brief 转矩单位。N·m.
	///
	///
	class Nm :
		public base::IUnit<Nm>
	{
	private:
		base::Fraction _value;

	public:
		Nm() = default;
		Nm(int64_t value);
		Nm(base::Fraction const &value);

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
