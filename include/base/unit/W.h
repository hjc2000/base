#pragma once
#include "base/math/Fraction.h"
#include "IUnit.h"

namespace base
{
	class W;
	class kW;

	///
	/// @brief 功率单位：瓦。
	///
	///
	class W :
		public base::IUnit<W>
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

		W(base::Fraction const &value)
		{
			_value = value;
		}

		W(base::kW const &value);

		using base::IUnit<W>::Value;

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
