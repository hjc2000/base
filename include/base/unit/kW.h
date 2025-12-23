#pragma once
#include "base/math/Fraction.h"
#include "IUnit.h"
#include "W.h"
#include <type_traits>

namespace base::unit
{
	///
	/// @brief 功率单位：千瓦。
	///
	///
	class kW :
		public base::unit::IUnit<kW>
	{
	private:
		base::Fraction _value;

	public:
		kW() = default;

		template <typename T>
			requires(std::is_convertible_v<T, base::Fraction>)
		explicit kW(T const &value)
		{
			_value = base::Fraction{value};
		}

		kW(base::unit::W const &value)
		{
			_value = value.Value() / 1000;
		}

		template <typename T>
			requires(std::is_convertible_v<T, base::unit::W>)
		kW(T const &value)
			: kW{base::unit::W{value}}
		{
		}

		using base::unit::IUnit<kW>::Value;

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
			return "kW";
		}

		operator base::unit::W() const
		{
			base::unit::W ret{_value * 1000};
			return ret;
		}
	};

} // namespace base::unit
