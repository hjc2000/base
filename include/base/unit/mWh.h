#pragma once
#include "base/math/Fraction.h"
#include "base/unit/J.h"
#include "IUnit.h"
#include "Wh.h"
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

		mWh(base::unit::J const &value)
		{
			base::unit::Wh wh{value};

			// Wh = 1000mWh
			_value = wh.Value() * 1000;
		}

		template <typename T>
			requires(std::is_convertible_v<T, base::unit::J>)
		mWh(T const &value)
			: mWh{base::unit::J{value}}
		{
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

		operator base::unit::J() const
		{
			// Wh = 1000mWh
			// 反过来
			// mWh = Wh / 1000
			base::unit::Wh wh{_value / 1000};
			base::unit::J ret{wh};
			return ret;
		}
	};

} // namespace base::unit
