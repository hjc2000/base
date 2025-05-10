#pragma once
#include "base/bit/AutoBitConverter.h"
#include "base/container/Array.h"
#include "base/math/Fraction.h"

namespace base
{
	namespace profidrive
	{
		///
		/// @brief profidrive 行规特定类型: X2.
		///
		///
		class X2 final
		{
		private:
			base::Fraction _value;

			///
			/// @brief 自适应转换器。
			///
			/// @note 将远程字节序设置为大端序后，在转换时能够根据本机字节序决定是否翻转。
			///
			base::AutoBitConverter _converter{std::endian::big};

			///
			/// @brief 系数。
			///
			/// @return int32_t
			///
			int32_t Factor() const
			{
				return static_cast<int64_t>(1 << 12);
			}

		public:
			X2() = default;

			///
			/// @brief 从 profinet 收到大端序的数据后原封不动地将字节序列传进来。
			///
			/// @param span
			///
			explicit X2(base::ReadOnlySpan const &span)
			{
				// 行规特定数据类型用一个整型来储存它的值，这个整型值可以认为是将分数的实际值乘上 Factor
				// 放大后截断为整型。
				//
				// 想要获得分数的实际值，就将这个整型除以 Factor.
				int16_t x2 = _converter.FromBytes<int16_t>(span);
				_value = base::Fraction{x2, Factor()};
			}

			///
			/// @brief 通过实际的分数值构造行规特定数据类型。
			///
			/// @param value
			///
			explicit X2(base::Fraction const &value)
			{
				_value = value;
			}

			explicit operator base::Fraction() const;
			base::Array<uint8_t, 2> BufferForSending() const;

			X2 operator+(X2 const &right_value) const
			{
				return base::profidrive::X2{_value + right_value._value};
			}

			X2 operator-(X2 const &right_value) const
			{
				return base::profidrive::X2{_value - right_value._value};
			}

			X2 operator*(X2 const &right_value) const
			{
				return base::profidrive::X2{_value * right_value._value};
			}

			X2 operator/(X2 const &right_value) const
			{
				return base::profidrive::X2{_value / right_value._value};
			}

			X2 &operator+=(X2 const &right_value)
			{
				_value += right_value._value;
				return *this;
			}

			X2 &operator-=(X2 const &right_value)
			{
				_value -= right_value._value;
				return *this;
			}

			X2 &operator*=(X2 const &right_value)
			{
				_value *= right_value._value;
				return *this;
			}

			X2 &operator/=(X2 const &right_value)
			{
				_value /= right_value._value;
				return *this;
			}
		};
	} // namespace profidrive
} // namespace base
