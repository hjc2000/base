#pragma once
#include "Ah.h"
#include "base/math/Fraction.h"
#include "IUnit.h"
#include <type_traits>

namespace base::unit
{
	///
	/// @brief 毫安时。
	///
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

		mAh(base::unit::Ah const &value)
		{
			_value = value.Value() * 1000;
		}

		template <typename T>
			requires(std::is_convertible_v<T, base::unit::Ah>)
		mAh(T const &value)
			: mAh{base::unit::Ah{value}}
		{
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

		operator base::unit::Ah() const
		{
			base::unit::Ah ret{_value / 1000};
			return ret;
		}
	};

} // namespace base::unit
