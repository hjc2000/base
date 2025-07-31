#pragma once
#include "base/unit/Hz.h"
#include "base/unit/IUnit.h"
#include "base/unit/Second.h"
#include <type_traits>

namespace base
{
	namespace unit
	{
		class Nanosecond;

		///
		/// @brief 频率单位：MHz.
		///
		///
		class MHz :
			public base::unit::IUnit<MHz>
		{
		private:
			base::Fraction _value{};

		public:
			MHz() = default;

			template <typename value_type>
				requires(std::is_integral_v<value_type>)
			explicit MHz(value_type value)
			{
				_value = value;
			}

			explicit MHz(base::Fraction const &value)
			{
				_value = value;
			}

			MHz(base::unit::Second const &value)
				: MHz(base::unit::Hz{value})
			{
			}

			explicit MHz(base::unit::Hz const &value);
			explicit MHz(base::unit::Nanosecond const &value);

			using base::unit::IUnit<MHz>::Value;

			///
			/// @brief 单位的值。
			///
			/// @return
			///
			virtual base::Fraction &Value() override;

			///
			/// @brief 单位的字符串。
			///
			/// @return
			///
			virtual std::string UnitString() const override;

			operator base::unit::Hz() const
			{
				base::unit::Hz ret{_value * 1000 * 1000};
				return ret;
			}

			operator base::unit::Second() const
			{
				base::unit::Hz hz{*this};
				return base::unit::Second{hz};
			}
		};

	} // namespace unit
} // namespace base
