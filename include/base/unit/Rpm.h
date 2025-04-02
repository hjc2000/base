#pragma once
#include "base/math/Fraction.h"
#include "base/unit/IUnit.h"
#include <cstdint>

namespace base
{
	class Rps;
	class Rpm;

	///
	/// @brief 转速。圈 / 分。
	///
	///
	class Rpm :
		public base::IUnit<Rpm>
	{
	private:
		base::Fraction _value;

	public:
		Rpm() = default;
		explicit Rpm(int64_t value);
		explicit Rpm(base::Fraction const &value);
		explicit Rpm(base::Rps const &value);

		using base::IUnit<Rpm>::Value;

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
