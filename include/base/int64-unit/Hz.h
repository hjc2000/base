#pragma once
#include "base/int64-unit/IUnit.h"
#include "base/int64-unit/Second.h"

namespace base
{
	namespace int64_unit
	{
		/// @brief 频率单位：Hz.
		class Hz :
			public base::int64_unit::IUnit<Hz>
		{
		private:
			base::Int64Fraction _value{};

		public:
			Hz() = default;

			template <typename value_type>
				requires(std::is_integral_v<value_type>)
			explicit Hz(value_type value)
			{
				_value = value;
			}

			explicit Hz(base::Int64Fraction const &value)
			{
				_value = value;
			}

			Hz(base::int64_unit::Second const &value)
			{
				_value = static_cast<base::Int64Fraction>(value).Reciprocal();
			}

			///
			/// @brief 能转换到 base::int64_unit::Second 的对象都借助 base::int64_unit::Second
			/// 进行构造。
			///
			template <typename T>
				requires(std::is_convertible_v<T, base::int64_unit::Second>)
			Hz(T const &value)
				: Hz(base::int64_unit::Second{value})
			{
			}

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
				return "Hz";
			}

			operator base::int64_unit::Second() const
			{
				base::int64_unit::Second ret{_value.Reciprocal()};
				return ret;
			}
		};

	} // namespace int64_unit
} // namespace base
