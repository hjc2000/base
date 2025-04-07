#pragma once
#include "base/math/Fraction.h"
#include "base/unit/IUnit.h"
#include <cstdint>

namespace base
{
	class Rps;
	class rpm;

	///
	/// @brief 转速。圈 / 秒。
	///
	///
	class Rps :
		public base::IUnit<Rps>
	{
	private:
		base::Fraction _value;

	public:
		Rps() = default;
		explicit Rps(int64_t value);
		explicit Rps(base::Fraction const &value);
		explicit Rps(base::rpm const &value);

		using base::IUnit<Rps>::Value;

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
