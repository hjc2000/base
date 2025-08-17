#pragma once
#include "base/define.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include <cstdint>

namespace base
{
	///
	/// @brief 利用 DMA 将数据从 src 内存段拷贝到 dst 内存段。
	///
	/// @note 实现者需要检查 src 和 dst 是否尺寸相等，不相等需要抛出异常。
	///
	/// @param src
	/// @param dst
	///
	void dma_copy(base::ReadOnlySpan const &src, base::Span const &dst);

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

	///
	/// @brief 利用 DMA 将数据从 [begin, end) 内存段拷贝到 dst 指针指向的位置。
	///
	/// @param begin
	/// @param end
	/// @param dst
	///
	IMPLEMENTED
	inline void dma_copy(uint8_t const *begin, uint8_t const *end, uint8_t *dst)
	{
		base::ReadOnlySpan src_span{begin, end - begin};
		base::Span dst_span{dst, end - begin};
		dma_copy(src_span, dst_span);
	}

} // namespace base
