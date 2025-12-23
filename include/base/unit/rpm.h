#pragma once
#include "base/math/Fraction.h"
#include "base/unit/IUnit.h"

namespace base::unit
{
	///
	/// @brief 转速。圈 / 分。
	///
	///
	class rpm :
		public base::unit::IUnit<rpm>
	{
	private:
		base::Fraction _value;

	public:
		rpm() = default;

		explicit rpm(base::Fraction const &value)
		{
			_value = value;
		}

		using base::unit::IUnit<rpm>::Value;

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
			return "rpm";
		}
	};

} // namespace base::unit
