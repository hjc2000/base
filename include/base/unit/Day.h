#pragma once
#include "base/math/Fraction.h"
#include "base/unit/Hour.h"
#include "base/unit/IUnit.h"
#include "base/unit/Second.h"
#include "IUnit.h"
#include <chrono>
#include <type_traits>

namespace base::unit
{
	class Day :
		public base::unit::IUnit<Day>
	{
	private:
		base::Fraction _value{};

	public:
		Day() = default;

		template <typename T>
			requires(std::is_convertible_v<T, base::Fraction>)
		explicit Day(T const &value)
		{
			_value = base::Fraction{value};
		}

		Day(base::unit::Second const &value)
		{
			base::unit::Hour hour{value};
			_value = hour.Value() / 24;
		}

		///
		/// @brief 能转换到 base::unit::Second 的对象都借助 base::unit::Second
		/// 进行构造。
		///
		template <typename T>
			requires(std::is_convertible_v<T, base::unit::Second>)
		Day(T const &value)
			: Day{base::unit::Second{value}}
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
			return "d";
		}

		explicit operator std::chrono::days() const
		{
			return std::chrono::days{base::unit::Second{*this}};
		}

		explicit operator std::chrono::hours() const
		{
			return std::chrono::hours{base::unit::Second{*this}};
		}

		explicit operator std::chrono::minutes() const
		{
			return std::chrono::minutes{base::unit::Second{*this}};
		}

		explicit operator std::chrono::seconds() const
		{
			return std::chrono::seconds{base::unit::Second{*this}};
		}

		explicit operator std::chrono::milliseconds() const
		{
			return std::chrono::milliseconds{base::unit::Second{*this}};
		}

		explicit operator std::chrono::microseconds() const
		{
			return std::chrono::microseconds{base::unit::Second{*this}};
		}

		explicit operator std::chrono::nanoseconds() const
		{
			return std::chrono::nanoseconds{base::unit::Second{*this}};
		}

		operator base::unit::Second() const
		{
			base::unit::Hour hour{_value * 24};
			return base::unit::Second{hour};
		}
	};

} // namespace base::unit
