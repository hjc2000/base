#pragma once
#include "base/net/profinet/DataItem.h"
#include "base/stream/Span.h"

namespace base
{
	namespace profinet
	{
		class C_SDU
		{
		private:
			base::Span _span;

		public:
			C_SDU() = default;
			C_SDU(base::Span const &span);

			base::Span const &Span() const;

			/// @brief 数据项。
			/// @return
			base::profinet::DataItem DataItem() const;
			void SetDataItem(base::profinet::DataItem const &value);

			/// @brief 填充的边距。
			/// @note C_SDU 的有效字节如果不足 40 字节，需要填充字节到 40 字节。填充的字节的值为 0.
			/// 这是因为带有 VLAN 标签的以太网帧的最小大小为 64 字节。里面塞入 PROFINET 的一些头尾
			/// 字段后，剩下的空间给 C_SDU，所以只能靠 C_SDU 来填充起来，使以太网的帧大小符合最小要求。
			/// @return
			base::Span Padding() const;
		};
	} // namespace profinet
} // namespace base
