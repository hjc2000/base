#pragma once
#include "base/bit/AutoBitConverter.h"
#include "base/container/Array.h"
#include "base/math/Fraction.h"

namespace base
{
	namespace profidrive
	{
		///
		/// @brief profidrive 行规特定类型: E2.
		///
		///
		class E2
		{
		private:
			base::Fraction _value;
			base::AutoBitConverter _converter{std::endian::big};

			///
			/// @brief 系数。
			///
			/// @return int32_t
			///
			int32_t Factor() const;

		public:
			E2() = default;

			///
			/// @brief 从 profinet 收到大端序的数据后原封不动地将字节序列传进来。
			///
			/// @param span
			///
			E2(base::ReadOnlySpan const &span);

			///
			/// @brief 通过实际的分数值构造行规特定数据类型。
			///
			/// @param value
			///
			E2(base::Fraction const &value);

			explicit operator base::Fraction() const;
			base::Array<uint8_t, 2> BufferForSending() const;

			E2 operator+(E2 const &right_value) const
			{
				return base::profidrive::E2{_value + right_value._value};
			}

			E2 operator-(E2 const &right_value) const
			{
				return base::profidrive::E2{_value - right_value._value};
			}

			E2 operator*(E2 const &right_value) const
			{
				return base::profidrive::E2{_value * right_value._value};
			}

			E2 operator/(E2 const &right_value) const
			{
				return base::profidrive::E2{_value / right_value._value};
			}

			E2 &operator+=(E2 const &right_value)
			{
				_value += right_value._value;
				return *this;
			}

			E2 &operator-=(E2 const &right_value)
			{
				_value -= right_value._value;
				return *this;
			}

			E2 &operator*=(E2 const &right_value)
			{
				_value *= right_value._value;
				return *this;
			}

			E2 &operator/=(E2 const &right_value)
			{
				_value /= right_value._value;
				return *this;
			}
		};
	} // namespace profidrive
} // namespace base
