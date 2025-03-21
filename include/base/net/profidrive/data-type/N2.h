#pragma once
#include "base/bit/AutoBitConverter.h"
#include "base/container/Array.h"
#include "base/math/Fraction.h"
#include "base/stream/ReadOnlySpan.h"

namespace base
{
	namespace profidrive
	{
		///
		/// @brief profidrive 行规特定类型: N2.
		///
		///
		class N2 final
		{
		private:
			base::Fraction _value;
			base::AutoBitConverter _converter{std::endian::big};

			int32_t Factor() const;

		public:
			N2() = default;

			///
			/// @brief 从 profinet 收到大端序的数据后原封不动地将字节序列传进来。
			///
			/// @param span
			///
			N2(base::ReadOnlySpan const &span);

			///
			/// @brief 通过实际的分数值构造行规特定数据类型。
			///
			/// @param value
			///
			N2(base::Fraction const &value);

			///
			/// @brief 强制转换为分数类型。
			///
			/// @return base::Fraction
			///
			explicit operator base::Fraction() const;

			base::Array<uint8_t, 2> BufferForSending() const;

			N2 operator+(N2 const &right_value) const
			{
				return base::profidrive::N2{_value + right_value._value};
			}

			N2 operator-(N2 const &right_value) const
			{
				return base::profidrive::N2{_value - right_value._value};
			}

			N2 operator*(N2 const &right_value) const
			{
				return base::profidrive::N2{_value * right_value._value};
			}

			N2 operator/(N2 const &right_value) const
			{
				return base::profidrive::N2{_value / right_value._value};
			}

			N2 &operator+=(N2 const &right_value)
			{
				_value += right_value._value;
				return *this;
			}

			N2 &operator-=(N2 const &right_value)
			{
				_value -= right_value._value;
				return *this;
			}

			N2 &operator*=(N2 const &right_value)
			{
				_value *= right_value._value;
				return *this;
			}

			N2 &operator/=(N2 const &right_value)
			{
				_value /= right_value._value;
				return *this;
			}
		};
	} // namespace profidrive
} // namespace base
