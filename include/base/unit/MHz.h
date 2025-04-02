#pragma once
#include "base/unit/IUnit.h"

namespace base
{
	class Seconds;
	class Nanoseconds;
	class Hz;

	///
	/// @brief 频率单位：MHz.
	///
	///
	class MHz :
		public base::IUnit<MHz>
	{
	private:
		base::Fraction _value{};

	public:
		MHz() = default;
		explicit MHz(base::Fraction const &value);
		explicit MHz(base::Hz const &value);
		explicit MHz(int64_t value);
		explicit MHz(base::Seconds const &value);
		explicit MHz(base::Nanoseconds const &value);

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
