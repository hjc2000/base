#pragma once
#include "base/int64-unit/Hz.h"
#include "base/int64-unit/IUnit.h"
#include "base/int64-unit/Second.h"
#include "base/math/Int64Fraction.h"
#include <type_traits>

namespace base
{
	namespace int64_unit
	{
		///
		/// @brief 频率单位：MHz.
		///
		///
		class MHz :
			public base::int64_unit::IUnit<MHz>
		{
		private:
			base::Int64Fraction _value{};

		public:
			MHz() = default;

			template <typename value_type>
				requires(std::is_integral_v<value_type>)
			explicit MHz(value_type value)
			{
				_value = value;
			}

			explicit MHz(base::Int64Fraction const &value)
			{
				_value = value;
			}

			MHz(base::int64_unit::Second const &value)
			{
				base::int64_unit::Hz hz{value};
				_value = hz.Value() / 1000 / 1000;
			}

			///
			/// @brief 能转换到 base::int64_unit::Second 的对象都借助 base::int64_unit::Second
			/// 进行构造。
			///
			template <typename T>
				requires(std::is_convertible_v<T, base::int64_unit::Second>)
			MHz(T const &value)
				: MHz(base::int64_unit::Second{value})
			{
			}

			using base::int64_unit::IUnit<MHz>::Value;

			///
			/// @brief 单位的值。
			///
			/// @return
			///
			virtual base::Int64Fraction &Value() override
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
				return "MHz";
			}

			operator base::int64_unit::Second() const
			{
				base::int64_unit::Hz hz{_value * 1000 * 1000};
				return base::int64_unit::Second{hz};
			}
		};

	} // namespace int64_unit
} // namespace base
