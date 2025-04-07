#pragma once
#include "base/unit/IUnit.h"

namespace base
{
	class Mbps;

	///
	/// @brief 比特率。每秒的比特数。这里是 bit / s.
	///
	///
	class bps :
		public base::IUnit<bps>
	{
	private:
		base::Fraction _value{};

	public:
		bps() = default;
		explicit bps(int64_t value);
		explicit bps(base::Fraction const &o);
		explicit bps(Mbps const &o);

		///
		/// @brief 单位的值。
		///
		/// @return base::Fraction&
		///
		virtual base::Fraction &Value() override;

		///
		/// @brief 单位的字符串。
		///
		/// @return std::string
		///
		virtual std::string UnitString() const override;
	};
} // namespace base
