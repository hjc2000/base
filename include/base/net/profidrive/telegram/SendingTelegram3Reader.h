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
		/// @brief 控制器发送的标准报文 3.
		///
		///
		class SendingTelegram3Reader
		{
		private:
			base::ReadOnlySpan _span;

		public:
			///
			/// @brief 构造函数。
			///
			/// @param span 将控制器发送的报文 3 传进来。
			///
			SendingTelegram3Reader(base::ReadOnlySpan const &span)
				: _span(span)
			{
				if (span.Size() < 10)
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
			/// @brief 控制字 1.
			///
			/// @return
			///
			base::profidrive::V2 STW1() const
			{
				base::ReadOnlySpan span = _span[base::Range{0, 2}];
				return base::profidrive::V2{span};
			}

			///
			/// @brief 给定转速。
			///
			/// @note 是个分数，表示是额定转速的多少倍。
			///
			/// @return
			///
			base::profidrive::N4 NSOLL_B() const
			{
				base::ReadOnlySpan span = _span[base::Range{2, 6}];
				return base::profidrive::N4{span};
			}

			///
			/// @brief 控制字 2.
			///
			/// @return
			///
			base::profidrive::V2 STW2() const
			{
				base::ReadOnlySpan span = _span[base::Range{6, 8}];
				return base::profidrive::V2{span};
			}

			///
			/// @brief 编码器 1 控制字。
			///
			/// @return
			///
			base::profidrive::V2 G1_STW() const
			{
				base::ReadOnlySpan span = _span[base::Range{8, 10}];
				return base::profidrive::V2{span};
			}

			/* #endregion */
		};
	} // namespace profidrive
} // namespace base
