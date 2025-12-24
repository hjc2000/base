#pragma once
#include "base/math/Fraction.h"
#include "IUnit.h"
#include <type_traits>

namespace base::unit
{
	///
	/// @brief 毫安时。
	///
	class mWh :
		public base::unit::IUnit<mWh>
	{
	private:
		base::Fraction _value;

	public:
		mWh() = default;

		template <typename T>
			requires(std::is_convertible_v<T, base::Fraction>)
		explicit mWh(T const &value)
		{
			_value = base::Fraction{value};
		}

		using base::unit::IUnit<mWh>::Value;

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
			return "mWh";
		}
	};

} // namespace base::unit
