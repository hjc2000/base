#pragma once
#include "base/math/Fraction.h"
#include "IUnit.h"

namespace base
{
	class W;
	class kW;

	///
	/// @brief 功率单位：千瓦。
	///
	///
	class kW :
		public base::IUnit<kW>
	{
	private:
		base::Fraction _value;

	public:
		kW() = default;

		template <typename value_type>
			requires(std::is_integral_v<value_type>)
		explicit kW(value_type value)
		{
			_value = value;
		}

		kW(base::Fraction const &value)
		{
			_value = value;
		}

		kW(base::W const &value);

		using base::IUnit<kW>::Value;

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
