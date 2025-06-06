#pragma once
#include "base/bit/AutoBitConverter.h"
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
		class N2
		{
		private:
			base::Fraction _value;
			base::AutoBitConverter _converter{std::endian::big};

			static constexpr int32_t Factor()
			{
				return static_cast<int64_t>(1 << 14);
			}

		public:
			/* #region 构造函数 */

			N2() = default;

			///
			/// @brief 从 profinet 收到大端序的数据后原封不动地将字节序列传进来。
			///
			/// @param span
			///
			explicit N2(base::ReadOnlySpan const &span)
			{
				// 行规特定数据类型用一个整型来储存它的值，这个整型值可以认为是将分数的实际值乘上 Factor
				// 放大后截断为整型。
				//
				// 想要获得分数的实际值，就将这个整型除以 Factor.
				int16_t n2 = _converter.FromBytes<int16_t>(span);
				_value = base::Fraction{n2, Factor()};
			}

			///
			/// @brief 通过实际的分数值构造行规特定数据类型。
			///
			/// @param value
			///
			explicit N2(base::Fraction const &value)
			{
				_value = value;
			}

			/* #endregion */

			base::Fraction const &Value() const
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
				if (span.Size() < 2)
				{
					throw std::invalid_argument{CODE_POS_STR + "传入的内存段过小。"};
				}

				// 行规特定数据类型用一个整型来储存它的值，这个整型值可以认为是将分数的实际值乘上 Factor
				// 放大后截断为整型。
				int16_t raw_value = static_cast<int16_t>(_value * Factor());
				_converter.GetBytes(raw_value, span);
			}
		};
	} // namespace profidrive
} // namespace base
