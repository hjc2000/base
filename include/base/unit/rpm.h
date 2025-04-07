#pragma once
#include "base/math/Fraction.h"
#include "base/unit/IUnit.h"
#include <cstdint>

namespace base
{
	class rps;
	class rpm;

	///
	/// @brief 转速。圈 / 分。
	///
	///
	class rpm :
		public base::IUnit<rpm>
	{
	private:
		base::Fraction _value;

	public:
		rpm() = default;
		explicit rpm(int64_t value);
		explicit rpm(base::Fraction const &value);
		explicit rpm(base::rps const &value);

		using base::IUnit<rpm>::Value;

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
