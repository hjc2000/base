#pragma once
#include "base/math/Fraction.h"
#include "base/unit/IUnit.h"

namespace base::unit
{
	///
	/// @brief 转矩单位。N·m.
	///
	///
	class Nm :
		public base::unit::IUnit<Nm>
	{
	private:
		base::Fraction _value;

	public:
		Nm() = default;

		template <typename value_type>
			requires(std::is_integral_v<value_type>)
		explicit Nm(value_type value)
		{
			_value = value;
		}

		explicit Nm(base::Fraction const &value)
		{
			_value = value;
		}

		using base::unit::IUnit<Nm>::Value;

		///
		/// @brief 单位的值。
		///
		/// @return
		///
		virtual base::Fraction &Value() override
		{
			return _value;
		}

		///
		/// @brief 单位的字符串。
		///
		/// @return
		///
		virtual std::string UnitString() const override
		{
			return "N·m";
		}
	};

} // namespace base::unit
