#pragma once
#include "base/int64-unit/IUnit.h"
#include "base/int64-unit/rpm.h"
#include "base/math/Int64Fraction.h"

namespace base
{
	namespace int64_unit
	{
		///
		/// @brief 转速。圈 / 秒。
		///
		///
		class rps :
			public base::int64_unit::IUnit<rps>
		{
		private:
			base::Int64Fraction _value;

		public:
			rps() = default;

			template <typename value_type>
				requires(std::is_integral_v<value_type>)
			explicit rps(value_type value)
			{
				_value = value;
			}

			explicit rps(base::Int64Fraction const &value)
			{
				_value = value;
			}

			rps(base::int64_unit::rpm const &value)
			{
				_value = value.Value() / 60;
			}

			///
			/// @brief 能转换到 base::int64_unit::rpm 的都借助 base::int64_unit::rpm 来初始化。
			///
			///
			template <typename T>
				requires(std::is_convertible_v<T, base::int64_unit::rpm>)
			rps(T const &value)
				: rps(base::int64_unit::rpm{value})
			{
			}

			using base::int64_unit::IUnit<rps>::Value;

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
				return "rps";
			}

			operator base::int64_unit::rpm() const
			{
				base::int64_unit::rpm ret{_value * 60};
				return ret;
			}
		};

	} // namespace int64_unit
} // namespace base
