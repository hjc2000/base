#pragma once
#include "base/math/Fraction.h"
#include "base/unit/J.h"
#include "IUnit.h"
#include "Wh.h"
#include <type_traits>

namespace base::unit
{
	class kWh :
		public base::unit::IUnit<kWh>
	{
	private:
		base::Fraction _value;

	public:
		kWh() = default;

		template <typename T>
			requires(std::is_convertible_v<T, base::Fraction>)
		explicit kWh(T const &value)
		{
			_value = base::Fraction{value};
		}

		kWh(base::unit::J const &value)
		{
			base::unit::Wh wh{value};

			// kWh = 1000 * Wh
			// Wh = kWh / 1000
			_value = wh.Value() / 1000;
		}

		template <typename T>
			requires(std::is_convertible_v<T, base::unit::J>)
		kWh(T const &value)
			: kWh{base::unit::J{value}}
		{
		}

		using base::unit::IUnit<kWh>::Value;

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
			return "kWh";
		}

		operator base::unit::J() const
		{
			// kWh = 1000 * Wh
			// Wh = kWh / 1000
			base::unit::Wh wh{_value * 1000};
			base::unit::J ret{wh};
			return ret;
		}
	};

} // namespace base::unit
