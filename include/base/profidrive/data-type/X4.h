#pragma once
#include "base/bit/AutoBitConverter.h"
#include "base/math/Int64Fraction.h"
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
			base::Int64Fraction _value;

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
			explicit X4(base::ReadOnlySpan const &span)
			{
				// 行规特定数据类型用一个整型来储存它的值，这个整型值可以认为是将分数的实际值乘上 Factor
				// 放大后截断为整型。
				//
				// 想要获得分数的实际值，就将这个整型除以 Factor.
				int32_t x4 = base::big_endian_remote_converter.FromBytes<int32_t>(span);
				_value = base::Int64Fraction{x4, Factor()};
			}

			///
			/// @brief 通过实际的分数值构造行规特定数据类型。
			///
			/// @param value
			///
			explicit X4(base::Int64Fraction const &value)
			{
				_value = value;
			}

			/* #endregion */

			base::Int64Fraction const &Value() const
			{
				return _value;
			}

			///
			/// @brief 将本对象序列化为字节序列，可以被发送到 profinet.
			///
			/// @param span
			///
			void GetBytes(base::Span const &span) const
			{
				if (span.Size() < 4)
				{
					throw std::invalid_argument{CODE_POS_STR + "传入的内存段过小。"};
				}

				// 行规特定数据类型用一个整型来储存它的值，这个整型值可以认为是将分数的实际值乘上 Factor
				// 放大后截断为整型。
				int32_t raw_value = static_cast<int32_t>(_value * Factor());
				base::big_endian_remote_converter.GetBytes(raw_value, span);
			}

			X4 operator+(X4 const &right_value) const
			{
				return profidrive::X4{_value + right_value._value};
			}

			X4 operator-(X4 const &right_value) const
			{
				return profidrive::X4{_value - right_value._value};
			}

			X4 operator*(X4 const &right_value) const
			{
				return profidrive::X4{_value * right_value._value};
			}

			X4 operator/(X4 const &right_value) const
			{
				return profidrive::X4{_value / right_value._value};
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
