#pragma once
#include "base/math/Fraction.h"
#include "base/unit/IUnit.h"
#include "base/unit/Minute.h"
#include "base/unit/Second.h"
#include "IUnit.h"
#include <chrono>
#include <type_traits>

namespace base::unit
{
	class Hour :
		public base::unit::IUnit<Hour>
	{
	private:
		base::Fraction _value{};

	public:
		Hour() = default;

		template <typename T>
			requires(std::is_convertible_v<T, base::Fraction>)
		explicit Hour(T const &value)
		{
			_value = base::Fraction{value};
		}

		Hour(base::unit::Second const &value)
		{
			base::unit::Minute minute{value};
			_value = minute.Value() / 60;
		}

		///
		/// @brief 能转换到 base::unit::Second 的对象都借助 base::unit::Second
		/// 进行构造。
		///
		template <typename T>
			requires(std::is_convertible_v<T, base::unit::Second>)
		Hour(T const &value)
			: Hour{base::unit::Second{value}}
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
			return "h";
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
			base::unit::Minute minute{_value * 60};
			return base::unit::Second{minute};
		}
	};

} // namespace base::unit
