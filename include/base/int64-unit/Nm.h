#pragma once
#include "base/int64-unit/IUnit.h"
#include "base/math/Int64Fraction.h"

namespace base
{
	namespace int64_unit
	{
		///
		/// @brief 转矩单位。N·m.
		///
		///
		class Nm :
			public base::int64_unit::IUnit<Nm>
		{
		private:
			base::Int64Fraction _value;

		public:
			Nm() = default;

			template <typename value_type>
				requires(std::is_integral_v<value_type>)
			explicit Nm(value_type value)
			{
				_value = value;
			}

			explicit Nm(base::Int64Fraction const &value)
			{
				_value = value;
			}

			using base::int64_unit::IUnit<Nm>::Value;

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
				return "N·m";
			}
		};

	} // namespace int64_unit
} // namespace base
