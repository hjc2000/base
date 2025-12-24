#pragma once
#include "base/math/Fraction.h"
#include "base/unit/W.h"
#include "IUnit.h"
#include <type_traits>

namespace base::unit
{
	///
	/// @brief 功率单位：毫瓦。
	///
	class mW :
		public base::unit::IUnit<mW>
	{
	private:
		base::Fraction _value;

	public:
		mW() = default;

		template <typename T>
			requires(std::is_convertible_v<T, base::Fraction>)
		explicit mW(T const &value)
		{
			_value = base::Fraction{value};
		}

		mW(base::unit::W const &value)
		{
			_value = value.Value() * 1000;
		}

		template <typename T>
			requires(std::is_convertible_v<T, base::unit::W>)
		mW(T const &value)
			: mW{base::unit::W{value}}
		{
		}

		using base::unit::IUnit<mW>::Value;

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
			return "mW";
		}

		operator base::unit::W() const
		{
			base::unit::W ret{_value / 1000};
			return ret;
		}
	};

} // namespace base::unit
