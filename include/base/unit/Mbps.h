#pragma once
#include "base/math/Fraction.h"
#include "base/unit/bps.h"
#include "base/unit/IUnit.h"
#include "IUnit.h"
#include <type_traits>

namespace base::unit
{
	///
	/// @brief 比特率。每秒的比特数。这里是 Mbit / s.
	///
	/// @note 在通信领域，1 Mbit = 1000 * 1000 bit.
	///
	class Mbps :
		public base::unit::IUnit<Mbps>
	{
	private:
		base::Fraction _value{};

	public:
		Mbps() = default;

		template <typename T>
			requires(std::is_convertible_v<T, base::Fraction>)
		explicit Mbps(T const &value)
		{
			_value = base::Fraction{value};
		}

		Mbps(base::unit::bps const &o)
		{
			_value = static_cast<base::Fraction>(o) / 1000 / 1000;
		}

		///
		/// @brief 能转换为 base::unit::bps 的对象都利用 base::unit::bps 进行初始化。
		///
		///
		template <typename T>
			requires(std::is_convertible_v<T, base::unit::bps>)
		Mbps(T const &value)
			: Mbps{base::unit::bps{value}}
		{
		}

		using base::unit::IUnit<Mbps>::Value;

		virtual base::Fraction &Value() override
		{
			return _value;
		}

		/// @brief 单位的字符串。
		/// @return
		virtual std::string UnitString() const override
		{
			return "Mbps";
		}

		operator base::unit::bps() const
		{
			base::unit::bps ret{_value * 1000 * 1000};
			return ret;
		}
	};

} // namespace base::unit
