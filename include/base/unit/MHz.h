#pragma once
#include "base/math/Fraction.h"
#include "base/unit/Hz.h"
#include "base/unit/IUnit.h"
#include "base/unit/Second.h"
#include "IUnit.h"
#include <type_traits>

namespace base::unit
{
	///
	/// @brief 频率单位：MHz.
	///
	///
	class MHz :
		public base::unit::IUnit<MHz>
	{
	private:
		base::Fraction _value{};

	public:
		MHz() = default;

		template <typename T>
			requires(std::is_convertible_v<T, base::Fraction>)
		explicit MHz(T const &value)
		{
			_value = base::Fraction{value};
		}

		MHz(base::unit::Second const &value)
		{
			base::unit::Hz hz{value};
			_value = hz.Value() / 1000 / 1000;
		}

		///
		/// @brief 能转换到 base::unit::Second 的对象都借助 base::unit::Second
		/// 进行构造。
		///
		template <typename T>
			requires(std::is_convertible_v<T, base::unit::Second>)
		MHz(T const &value)
			: MHz{base::unit::Second{value}}
		{
		}

		using base::unit::IUnit<MHz>::Value;

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
			return "MHz";
		}

		operator base::unit::Second() const
		{
			base::unit::Hz hz{_value * 1000 * 1000};
			return base::unit::Second{hz};
		}
	};

} // namespace base::unit
