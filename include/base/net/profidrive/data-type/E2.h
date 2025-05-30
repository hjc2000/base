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
			int32_t Factor() const
			{
				return static_cast<int64_t>(1 << 7);
			}

		public:
			/* #region 构造函数 */

			E2() = default;

			///
			/// @brief 从 profinet 收到大端序的数据后原封不动地将字节序列传进来。
			///
			/// @param span
			///
			explicit E2(base::ReadOnlySpan const &span)
			{
				// 行规特定数据类型用一个整型来储存它的值，这个整型值可以认为是将分数的实际值乘上 Factor
				// 放大后截断为整型。
				//
				// 想要获得分数的实际值，就将这个整型除以 Factor.
				int16_t e2 = _converter.FromBytes<int16_t>(span);
				_value = base::Fraction{e2, Factor()};
			}

			///
			/// @brief 通过实际的分数值构造行规特定数据类型。
			///
			/// @param value
			///
			explicit E2(base::Fraction const &value)
			{
				_value = value;
			}

			/* #endregion */

			base::Fraction const &Value() const
			{
				return _value;
			}

			base::Array<uint8_t, 2> BufferForSending() const
			{
				// 行规特定数据类型用一个整型来储存它的值，这个整型值可以认为是将分数的实际值乘上 Factor
				// 放大后截断为整型。
				int16_t e2 = static_cast<int16_t>(_value * Factor());

				base::Array<uint8_t, 2> buffer;
				_converter.GetBytes(e2, buffer.Span());
				return buffer;
			}

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
