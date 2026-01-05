#pragma once
#include "base/math/Fraction.h"
#include "base/unit/IUnit.h"
#include "base/unit/rpm.h"
#include "IUnit.h"
#include <type_traits>

namespace base::unit
{
	///
	/// @brief 转速。圈 / 秒。
	///
	///
	class rps :
		public base::unit::IUnit<rps>
	{
	private:
		base::Fraction _value;

	public:
		rps() = default;

		template <typename T>
			requires(std::is_convertible_v<T, base::Fraction>)
		explicit rps(T const &value)
		{
			_value = base::Fraction{value};
		}

		rps(base::unit::rpm const &value)
		{
			_value = value.Value() / 60;
		}

		///
		/// @brief 能转换到 base::unit::rpm 的都借助 base::unit::rpm 来初始化。
		///
		///
		template <typename T>
			requires(std::is_convertible_v<T, base::unit::rpm>)
		rps(T const &value)
			: rps(base::unit::rpm{value})
		{
		}

		using base::unit::IUnit<rps>::Value;

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
			return "rps";
		}

		operator base::unit::rpm() const
		{
			base::unit::rpm ret{_value * 60};
			return ret;
		}
	};

} // namespace base::unit
