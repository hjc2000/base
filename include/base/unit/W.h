#pragma once
#include "base/math/Fraction.h"
#include "IUnit.h"

namespace base::unit
{
	///
	/// @brief 功率单位：瓦。
	///
	class W :
		public base::unit::IUnit<W>
	{
	private:
		base::Fraction _value;

	public:
		W() = default;

		template <typename value_type>
			requires(std::is_integral_v<value_type>)
		explicit W(value_type value)
		{
			_value = value;
		}

		explicit W(base::Fraction const &value)
		{
			_value = value;
		}

		using base::unit::IUnit<W>::Value;

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
			return "W";
		}
	};

} // namespace base::unit
