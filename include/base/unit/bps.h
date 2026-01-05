#pragma once
#include "base/math/Fraction.h"
#include "base/unit/IUnit.h"
#include "IUnit.h"
#include <type_traits>

namespace base::unit
{
	///
	/// @brief 比特率。每秒的比特数。这里是 bit / s.
	///
	///
	class bps :
		public base::unit::IUnit<bps>
	{
	private:
		base::Fraction _value{};

	public:
		bps() = default;

		template <typename T>
			requires(std::is_convertible_v<T, base::Fraction>)
		explicit bps(T const &value)
		{
			_value = base::Fraction{value};
		}

		using base::unit::IUnit<bps>::Value;

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
			return "bps";
		}
	};

} // namespace base::unit
