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
		/// @brief profidrive 行规特定类型: N4.
		///
		///
		class N4
		{
		private:
			base::Fraction _value;
			base::AutoBitConverter _converter{std::endian::big};

			static constexpr int32_t Factor()
			{
				// 2 的 30 次方
				return static_cast<int64_t>(1 << 30);
			}

		public:
			/* #region 构造函数 */

			N4() = default;

			///
			/// @brief 从 profinet 收到大端序的数据后原封不动地将字节序列传进来。
			///
			/// @param span
			///
			N4(base::ReadOnlySpan const &span)
			{
				// 行规特定数据类型用一个整型来储存它的值，这个整型值可以认为是将分数的实际值乘上
				// Factor 放大后截断为整型。
				//
				// 想要获得分数的实际值，就将这个整型除以 Factor.
				int32_t n4 = _converter.FromBytes<int32_t>(span);
				_value = base::Fraction{n4, Factor()};
			}

			///
			/// @brief 通过实际的分数值构造行规特定数据类型。
			///
			/// @param value
			///
			N4(base::Fraction const &value)
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
				int32_t n4 = static_cast<int32_t>(_value * Factor());

				base::Array<uint8_t, 4> buffer;
				_converter.GetBytes(n4, buffer.Span());
				return buffer;
			}
		};
	} // namespace profidrive
} // namespace base
