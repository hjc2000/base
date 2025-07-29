#pragma once
#include "base/math/Fraction.h"
#include "base/unit/IUnit.h"
#include <cstdint>

namespace base
{
	namespace unit
	{
		class rps;
		class rpm;

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

			template <typename value_type>
				requires(std::is_integral_v<value_type>)
			explicit rps(value_type value)
			{
				_value = value;
			}

			explicit rps(base::Fraction const &value);
			explicit rps(base::unit::rpm const &value);

			using base::unit::IUnit<rps>::Value;

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

	} // namespace unit
} // namespace base
