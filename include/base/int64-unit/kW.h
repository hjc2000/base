#pragma once
#include "base/math/Int64Fraction.h"
#include "IUnit.h"
#include "W.h"

namespace base
{
	namespace int64_unit
	{
		///
		/// @brief 功率单位：千瓦。
		///
		///
		class kW :
			public base::int64_unit::IUnit<kW>
		{
		private:
			base::Int64Fraction _value;

		public:
			kW() = default;

			template <typename value_type>
				requires(std::is_integral_v<value_type>)
			explicit kW(value_type value)
			{
				_value = value;
			}

			explicit kW(base::Int64Fraction const &value)
			{
				_value = value;
			}

			kW(base::int64_unit::W const &value)
			{
				_value = value.Value() / 1000;
			}

			template <typename T>
				requires(std::is_convertible_v<T, base::int64_unit::W>)
			kW(T const &value)
				: kW(base::int64_unit::W{value})
			{
			}

			using base::int64_unit::IUnit<kW>::Value;

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
				return "kW";
			}

			operator base::int64_unit::W() const
			{
				base::int64_unit::W ret{_value * 1000};
				return ret;
			}
		};

	} // namespace int64_unit
} // namespace base
