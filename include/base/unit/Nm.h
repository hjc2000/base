#pragma once
#include "base/math/Fraction.h"
#include "base/unit/IUnit.h"
#include "IUnit.h"
#include <type_traits>

namespace base::unit
{
	///
	/// @brief 转矩单位。N·m.
	///
	///
	class Nm :
		public base::unit::IUnit<Nm>
	{
	private:
		base::Fraction _value;

	public:
		Nm() = default;

		template <typename T>
			requires(std::is_convertible_v<T, base::Fraction>)
		explicit Nm(T const &value)
		{
			_value = base::Fraction{value};
		}

		using base::unit::IUnit<Nm>::Value;

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
			return "N·m";
		}
	};

} // namespace base::unit
