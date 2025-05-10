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
			int32_t Factor() const
			{
				return static_cast<int64_t>(1 << 28);
			}

		public:
			/* #region 构造函数 */

			X4() = default;

			///
			/// @brief 从 profinet 收到大端序的数据后原封不动地将字节序列传进来。
			///
			/// @param span
			///
			X4(base::ReadOnlySpan const &span)
			{
				// 行规特定数据类型用一个整型来储存它的值，这个整型值可以认为是将分数的实际值乘上 Factor
				// 放大后截断为整型。
				//
				// 想要获得分数的实际值，就将这个整型除以 Factor.
				int32_t x4 = _converter.FromBytes<int32_t>(span);
				_value = base::Fraction{x4, Factor()};
			}

			///
			/// @brief 通过实际的分数值构造行规特定数据类型。
			///
			/// @param value
			///
			X4(base::Fraction const &value)
			{
				_value = value;
			}

			/* #endregion */

			base::Fraction const &Value() const
			{
				return _value;
			}

			base::Array<uint8_t, 4> BufferForSending() const
			{
				// 行规特定数据类型用一个整型来储存它的值，这个整型值可以认为是将分数的实际值乘上 Factor
				// 放大后截断为整型。
				int32_t x4 = static_cast<int32_t>(_value * Factor());

				base::Array<uint8_t, 4> buffer;
				_converter.GetBytes(x4, buffer.Span());
				return buffer;
			}

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
