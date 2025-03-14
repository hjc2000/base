#pragma once
#include <base/unit/IUnit.h>

namespace base
{
	class Mbps;

	/**
	 * @brief 比特率。每秒的比特数。这里是 bit / s.
	 *
	 */
	class Bps :
		public base::IUnit<Bps>
	{
	private:
		base::Fraction _value{};

	public:
		Bps() = default;
		explicit Bps(int64_t value);
		explicit Bps(base::Fraction const &o);
		explicit Bps(Mbps const &o);

	public:
		virtual base::Fraction &Value() override
		{
			return _value;
		}

		/**
		 * @brief 单位的字符串。
		 *
		 * @return std::string
		 */
		virtual std::string UnitString() const override;
	};
} // namespace base
