#pragma once
#include "base/math/Fraction.h"
#include "base/unit/IUnit.h"
#include <cstdint>

namespace base
{
	class rps;
	class rpm;

	///
	/// @brief 转速。圈 / 秒。
	///
	///
	class rps :
		public base::IUnit<rps>
	{
	private:
		base::Fraction _value;

	public:
		rps() = default;
		explicit rps(int64_t value);
		explicit rps(base::Fraction const &value);
		explicit rps(base::rpm const &value);

		using base::IUnit<rps>::Value;

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
