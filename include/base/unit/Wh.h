#pragma once
#include "base/math/Fraction.h"
#include "base/unit/J.h"
#include "IUnit.h"
#include <type_traits>

namespace base::unit
{
	class Wh :
		public base::unit::IUnit<Wh>
	{
	private:
		base::Fraction _value;

	public:
		Wh() = default;

		template <typename T>
			requires(std::is_convertible_v<T, base::Fraction>)
		explicit Wh(T const &value)
		{
			_value = base::Fraction{value};
		}

		Wh(base::unit::J const &value)
		{
			// Wh = W * s * 3600
			// = J * 3600
			//
			// 反过来
			// J = Wh / 3600
			_value = value.Value() / 3600;
		}

		template <typename T>
			requires(std::is_convertible_v<T, base::unit::J>)
		Wh(T const &value)
			: Wh{base::unit::J{value}}
		{
		}

		using base::unit::IUnit<Wh>::Value;

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
			return "Wh";
		}

		operator base::unit::J() const
		{
			// Wh = W * s * 3600
			// = J * 3600
			//
			// 反过来
			// J = Wh / 3600
			base::unit::J ret{_value * 3600};
			return ret;
		}
	};

} // namespace base::unit
