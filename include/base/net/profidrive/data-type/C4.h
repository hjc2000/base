#pragma once
#include "base/bit/AutoBitConverter.h"
#include "base/math/Fraction.h"
#include "base/stream/ReadOnlySpan.h"
#include <base/container/Array.h>

namespace base
{
	namespace profidrive
	{
		/**
		 * @brief profidrive 行规特定类型: C4.
		 *
		 */
		class C4 final
		{
		private:
			base::Fraction _value;

			/**
			 * @brief 自适应转换器。
			 * @note 将远程字节序设置为大端序后，在转换时能够根据本机字节序决定是否翻转。
			 */
			base::AutoBitConverter _converter{std::endian::big};

			int32_t Factor() const;

		public:
			/**
			 * @brief 无参构造函数。
			 *
			 */
			C4() = default;

			/**
			 * @brief 从 profinet 收到大端序的数据后原封不动地将字节序列传进来。
			 *
			 * @param span
			 */
			C4(base::ReadOnlySpan const &span);

			/**
			 * @brief 通过实际的分数值构造行规特定数据类型。
			 *
			 * @param value
			 */
			C4(base::Fraction const &value);

		public:
			/**
			 * @brief 强制转换为分数类型。
			 *
			 * @return base::Fraction
			 */
			explicit operator base::Fraction() const;

			base::Array<uint8_t, 4> BufferForSending() const;

		public:
			C4 operator+(C4 const &right_value) const
			{
				return base::profidrive::C4{_value + right_value._value};
			}

			C4 operator-(C4 const &right_value) const
			{
				return base::profidrive::C4{_value - right_value._value};
			}

			C4 operator*(C4 const &right_value) const
			{
				return base::profidrive::C4{_value * right_value._value};
			}

			C4 operator/(C4 const &right_value) const
			{
				return base::profidrive::C4{_value / right_value._value};
			}

			C4 &operator+=(C4 const &right_value)
			{
				_value += right_value._value;
				return *this;
			}

			C4 &operator-=(C4 const &right_value)
			{
				_value -= right_value._value;
				return *this;
			}

			C4 &operator*=(C4 const &right_value)
			{
				_value *= right_value._value;
				return *this;
			}

			C4 &operator/=(C4 const &right_value)
			{
				_value /= right_value._value;
				return *this;
			}
		};
	} // namespace profidrive
} // namespace base
