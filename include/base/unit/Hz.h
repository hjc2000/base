#pragma once
#include "base/math/Fraction.h"
#include "base/unit/IUnit.h"
#include "base/unit/Second.h"
#include "IUnit.h"
#include <type_traits>

namespace base::unit
{
	/// @brief 频率单位：Hz.
	class Hz :
		public base::unit::IUnit<Hz>
	{
	private:
		base::Fraction _value{};

	public:
		Hz() = default;

		template <typename T>
			requires(std::is_convertible_v<T, base::Fraction>)
		explicit Hz(T const &value)
		{
			_value = base::Fraction{value};
		}

		Hz(base::unit::Second const &value)
		{
			_value = static_cast<base::Fraction>(value).Reciprocal();
		}

		///
		/// @brief 能转换到 base::unit::Second 的对象都借助 base::unit::Second
		/// 进行构造。
		///
		template <typename T>
			requires(std::is_convertible_v<T, base::unit::Second>)
		Hz(T const &value)
			: Hz{base::unit::Second{value}}
		{
		}

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
			return "Hz";
		}

		operator base::unit::Second() const
		{
			base::unit::Second ret{_value.Reciprocal()};
			return ret;
		}
	};

} // namespace base::unit
