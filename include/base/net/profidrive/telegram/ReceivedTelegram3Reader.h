#pragma once
#include "base/container/Range.h"
#include "base/net/profidrive/data-type/N4.h"
#include "base/net/profidrive/data-type/V2.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/string/define.h"
#include <stdexcept>

namespace base
{
	namespace profidrive
	{
		///
		/// @brief 控制器接收的标准报文 3 的内存段阅读器。
		///
		///
		class ReceivedTelegram3Reader
		{
		private:
			base::ReadOnlySpan _span;

		public:
			///
			/// @brief 构造函数。
			///
			/// @param span 将控制器发送的报文 3 传进来。
			///
			ReceivedTelegram3Reader(base::ReadOnlySpan const &span)
				: _span(span)
			{
				if (span.Size() < 18)
				{
					throw std::invalid_argument{CODE_POS_STR + "内存段过小。"};
				}
			}

			base::ReadOnlySpan const &Span() const
			{
				return _span;
			}

			/* #region 报文的各个字段 */

			///
			/// @brief 状态字 1.
			///
			/// @return
			///
			base::profidrive::V2 ZSW1() const
			{
				base::ReadOnlySpan span = _span[base::Range{0, 2}];
				return base::profidrive::V2{span};
			}

			///
			/// @brief 实际转速。
			///
			/// @return
			///
			base::profidrive::N4 NIST_B() const
			{
				base::ReadOnlySpan span = _span[base::Range{2, 6}];
				return base::profidrive::N4{span};
			}

			///
			/// @brief 状态字 2.
			///
			/// @return
			///
			base::profidrive::V2 ZSW2() const
			{
				base::ReadOnlySpan span = _span[base::Range{6, 8}];
				return base::profidrive::V2{span};
			}

			///
			/// @brief 编码器 1 状态字。
			///
			/// @return
			///
			base::profidrive::V2 G1_ZSW() const
			{
				base::ReadOnlySpan span = _span[base::Range{8, 10}];
				return base::profidrive::V2{span};
			}

			///
			/// @brief 编码器实际位置 1.
			///
			/// @return
			///
			base::profidrive::N4 G1_XIST1() const
			{
				base::ReadOnlySpan span = _span[base::Range{10, 14}];
				return base::profidrive::N4{span};
			}

			///
			/// @brief 编码器实际位置 2.
			///
			/// @return
			///
			base::profidrive::N4 G1_XIST2() const
			{
				base::ReadOnlySpan span = _span[base::Range{14, 18}];
				return base::profidrive::N4{span};
			}

			/* #endregion */
		};
	} // namespace profidrive
} // namespace base
