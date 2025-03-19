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
		/// @brief profidrive 行规特定类型: X4.
		///
		///
		class X4 final
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
			X4() = default;

			///
			/// @brief 从 profinet 收到大端序的数据后原封不动地将字节序列传进来。
			///
			/// @param span
			///
			X4(base::ReadOnlySpan const &span);

			///
			/// @brief 通过实际的分数值构造行规特定数据类型。
			///
			/// @param value
			///
			X4(base::Fraction const &value);

			explicit operator base::Fraction() const;
			base::Array<uint8_t, 4> BufferForSending() const;

			X4 operator+(X4 const &right_value) const
			{
				return base::profidrive::X4{_value + right_value._value};
			}

			X4 operator-(X4 const &right_value) const
			{
				return base::profidrive::X4{_value - right_value._value};
			}

			X4 operator*(X4 const &right_value) const
			{
				return base::profidrive::X4{_value * right_value._value};
			}

			X4 operator/(X4 const &right_value) const
			{
				return base::profidrive::X4{_value / right_value._value};
			}

			X4 &operator+=(X4 const &right_value)
			{
				_value += right_value._value;
				return *this;
			}

			X4 &operator-=(X4 const &right_value)
			{
				_value -= right_value._value;
				return *this;
			}

			X4 &operator*=(X4 const &right_value)
			{
				_value *= right_value._value;
				return *this;
			}

			X4 &operator/=(X4 const &right_value)
			{
				_value /= right_value._value;
				return *this;
			}
		};
	} // namespace profidrive
} // namespace base
