#pragma once
#include "base/int64-unit/IUnit.h"
#include "base/math/Int64Fraction.h"

namespace base
{
	namespace int64_unit
	{
		///
		/// @brief 转速。圈 / 分。
		///
		///
		class rpm :
			public base::int64_unit::IUnit<rpm>
		{
		private:
			base::Int64Fraction _value;

		public:
			rpm() = default;

			template <typename value_type>
				requires(std::is_integral_v<value_type>)
			explicit rpm(value_type value)
			{
				_value = value;
			}

			explicit rpm(base::Int64Fraction const &value)
			{
				_value = value;
			}

			using base::int64_unit::IUnit<rpm>::Value;

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
				return "rpm";
			}
		};

	} // namespace int64_unit
} // namespace base
