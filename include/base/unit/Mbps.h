#pragma once
#include "base/unit/IUnit.h"

namespace base
{
	namespace unit
	{
		class bps;

		/// @brief 比特率。每秒的比特数。这里是 Mbit / s.
		/// @note 在通信领域，1 Mbit = 1000 * 1000 bit.
		class Mbps :
			public base::IUnit<Mbps>
		{
		private:
			base::Fraction _value{};

		public:
			Mbps() = default;

			template <typename value_type>
				requires(std::is_integral_v<value_type>)
			explicit Mbps(value_type value)
			{
				_value = value;
			}

			explicit Mbps(base::Fraction const &o);
			explicit Mbps(base::unit::bps const &o);

		public:
			virtual base::Fraction &Value() override
			{
				return _value;
			}

			/// @brief 单位的字符串。
			/// @return
			virtual std::string UnitString() const override;
		};

	} // namespace unit
} // namespace base
