#pragma once
#include "base/define.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include "base/string/define.h"
#include <cstdint>
#include <stdexcept>

namespace base
{
	///
	/// @brief 利用 DMA 将数据从 [begin, end) 内存段拷贝到 dst 指针指向的位置。
	///
	/// @param begin 元数据内存段的起始位置。
	/// @param end 元数据内存段的结束位置。
	/// @param dst 要将数据拷贝到的目的地址。
	///
	void dma_copy(uint8_t const *begin, uint8_t const *end, uint8_t *dst);

	///
	/// @brief 利用 DMA 将数据从 src 内存段拷贝到 dst 内存段。
	///
	/// @param src
	/// @param dst
	///
	IMPLEMENTED
	inline void dma_copy(base::ReadOnlySpan const &src, base::Span const &dst)
	{
		if (src.Size() != dst.Size())
		{
			throw std::invalid_argument{CODE_POS_STR + "要 src 和 dst 的大小不相等。"};
		}

		dma_copy(src.Buffer(), src.Buffer() + src.Size(), dst.Buffer());
	}

	///
	/// @brief 利用 DMA 将数据从 [begin, end) 内存段拷贝到 dst 内存段。
	///
	/// @param begin
	/// @param end
	/// @param dst
	///
	IMPLEMENTED
	inline void dma_copy(uint8_t const *begin, uint8_t const *end, base::Span dst)
	{
		base::ReadOnlySpan src_span{begin, end - begin};
		dma_copy(src_span, dst);
	}

} // namespace base
