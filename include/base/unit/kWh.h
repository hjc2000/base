#pragma once
#include "base/math/Fraction.h"
#include "base/unit/J.h"
#include "IUnit.h"
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
			// kWh = 1000 * Wh
			// = W * h * 1000
			// = W * s * 3600 * 1000
			// = J * 3600 * 1000
			//
			// 反过来
			// J = kWh / 3600 / 1000
			_value = value.Value() / 3600 / 1000;
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
			// = W * h * 1000
			// = W * s * 3600 * 1000
			// = J * 3600 * 1000
			//
			// 反过来
			// J = kWh / 3600 / 1000
			base::unit::J ret{_value * 3600 * 1000};
			return ret;
		}
	};

} // namespace base::unit
