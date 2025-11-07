#pragma once
#include "base/math/Int64Fraction.h"
#include "IUnit.h"

namespace base
{
	namespace int64_unit
	{
		///
		/// @brief 功率单位：瓦。
		///
		///
		class W :
			public base::int64_unit::IUnit<W>
		{
		private:
			base::Int64Fraction _value;

		public:
			W() = default;

			template <typename value_type>
				requires(std::is_integral_v<value_type>)
			explicit W(value_type value)
			{
				_value = value;
			}

			explicit W(base::Int64Fraction const &value)
			{
				_value = value;
			}

			using base::int64_unit::IUnit<W>::Value;

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
				return "W";
			}
		};

	} // namespace int64_unit
} // namespace base
