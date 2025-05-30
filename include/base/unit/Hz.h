#pragma once
#include "base/unit/IUnit.h"

namespace base
{
	class Seconds;
	class Nanoseconds;
	class MHz;

	/// @brief 频率单位：Hz.
	class Hz :
		public base::IUnit<Hz>
	{
	private:
		base::Fraction _value{};

	public:
		Hz() = default;

		template <typename value_type>
			requires(std::is_integral_v<value_type>)
		explicit Hz(value_type value)
		{
			_value = value;
		}

		explicit Hz(base::Fraction const &value);
		explicit Hz(base::MHz const &value);
		explicit Hz(base::Seconds const &value);
		explicit Hz(base::Nanoseconds const &value);

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
