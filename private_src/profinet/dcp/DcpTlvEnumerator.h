#pragma once
#include <base/bit/AutoBitConverter.h>
#include <base/container/iterator/IEnumerator.h>
#include <base/stream/ReadOnlySpan.h>

namespace base
{
	namespace profinet
	{
		/// @brief 迭代一段 base::ReadOnlySpan 中的 TLV.
		class DcpTlvEnumerator :
			public base::IEnumerator<base::ReadOnlySpan>
		{
		private:
			base::ReadOnlySpan _span;
			base::ReadOnlySpan _remain_span;
			base::ReadOnlySpan _current_value;
			base::AutoBitConverter _converter{std::endian::big};

		public:
			/// @brief 构造函数。
			/// @param span 含有很多 TLV 的 base::ReadOnlySpan.
			DcpTlvEnumerator(base::ReadOnlySpan const &span);

			/// @brief 获取当前值的引用
			/// @return
			base::ReadOnlySpan &CurrentValue() override;

			/// @brief 迭代器前进到下一个值
			/// @return
			bool MoveNext() override;

			/// @brief 将迭代器重置到容器开始的位置。
			/// @note 开始位置是第一个元素前。也就是说重置后，要调用一次 MoveNext 才能获取到第一个值。
			void Reset() override;
		};
	} // namespace profinet
} // namespace base
