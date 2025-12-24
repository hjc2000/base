#pragma once
#include "base/math/Fraction.h"
#include "IUnit.h"
#include <type_traits>

namespace base
{
	class mAh :
		public base::unit::IUnit<mAh>
	{
	private:
		base::Fraction _value;

	public:
		mAh() = default;

		template <typename T>
			requires(std::is_convertible_v<T, base::Fraction>)
		explicit mAh(T const &value)
		{
			_value = base::Fraction{value};
		}

		using base::unit::IUnit<mAh>::Value;

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
			return "mAh";
		}
	};

} // namespace base
