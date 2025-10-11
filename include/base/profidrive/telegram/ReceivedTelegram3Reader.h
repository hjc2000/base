#pragma once
#include "base/bit/AutoBitConverter.h"
#include "base/container/Range.h"
#include "base/profidrive/data-type/N4.h"
#include "base/profidrive/data-type/V2.h"
#include "base/profidrive/telegram/ReceivedTelegram3.h"
#include "base/stream/ReadOnlySpan.h"
#include <cstdint>

namespace base::profidrive
{
	///
	/// @brief 控制器接收的标准报文 3 的内存段读者。
	///
	class ReceivedTelegram3Reader
	{
	private:
		base::ReadOnlySpan _span;

	public:
		///
		/// @brief 构造函数。
		///
		/// @param span
		///
		ReceivedTelegram3Reader(base::ReadOnlySpan const &span);

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
		uint32_t G1_XIST1() const
		{
			base::ReadOnlySpan span = _span[base::Range{10, 14}];
			uint32_t value = base::big_endian_remote_converter.FromBytes<uint32_t>(span);
			return value;
		}

		///
		/// @brief 编码器实际位置 2.
		///
		/// @return
		///
		uint32_t G1_XIST2() const
		{
			base::ReadOnlySpan span = _span[base::Range{14, 18}];
			uint32_t value = base::big_endian_remote_converter.FromBytes<uint32_t>(span);
			return value;
		}

		/* #endregion */

		///
		/// @brief 读出整个报文 3.
		///
		/// @return
		///
		base::profidrive::ReceivedTelegram3 Read() const;
	};

} // namespace base::profidrive
