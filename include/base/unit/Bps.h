#pragma once
#include <base/unit/IUnit.h>

namespace base
{
	class Mbps;

	/// @brief 比特率。每秒的比特数。这里是 bit / s.
	class Bps :
		public base::IUnit<Bps>
	{
	private:
		base::Fraction _value = 0;

	public:
		Bps() = default;
		Bps(int64_t value);
		Bps(base::Fraction const &o);
		Bps(Mbps const &o);
		Bps(Bps const &o);
		base::Bps &operator=(Bps const &o);

		virtual base::Fraction &Value() override
		{
			return _value;
		}
	};
} // namespace base
