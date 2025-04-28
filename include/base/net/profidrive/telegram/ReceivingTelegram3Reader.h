#pragma once
#include "base/container/Range.h"
#include "base/net/profidrive/data-type/N4.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/unit/rpm.h"

namespace base
{
	namespace profidrive
	{
		///
		/// @brief 控制器接收的标准报文 3.
		///
		///
		class ReceivingTelegram3Reader
		{
		private:
			base::ReadOnlySpan _span;
			base::rpm _rated_speed;

		public:
			///
			/// @brief 构造函数。
			///
			/// @param span 将控制器接收的报文 3 传进来。
			/// @param rated_speed 额定转速。
			///
			ReceivingTelegram3Reader(base::ReadOnlySpan const &span,
									 base::rpm const &rated_speed)
				: _span(span),
				  _rated_speed(rated_speed)
			{
			}

			base::ReadOnlySpan Span() const
			{
				return _span;
			}

			/* #region 报文的各个字段 */

			base::ReadOnlySpan STW1() const
			{
				return _span[base::Range{0, 2}];
			}

			///
			/// @brief 给定转速。
			///
			/// @return
			///
			base::profidrive::N4 NSOLL_B() const
			{
				return base::profidrive::N4{_span[base::Range{2, 6}]};
			}

			base::ReadOnlySpan STW2() const
			{
				return _span[base::Range{6, 8}];
			}

			base::ReadOnlySpan G1_STW() const
			{
				return _span[base::Range{8, 10}];
			}

			/* #endregion */

			///
			/// @brief 给定速度。
			///
			/// @return
			///
			base::rpm GivenSpeed() const
			{
				return base::rpm{NSOLL_B().Value()};
			}
		};
	} // namespace profidrive
} // namespace base
