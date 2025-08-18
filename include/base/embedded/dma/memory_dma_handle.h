#pragma once
#include "base/define.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include "base/string/define.h"
#include <cstddef>
#include <cstdint>
#include <memory>
#include <stdexcept>

namespace base
{
	namespace memory_dma
	{
		///
		/// @brief 内存 DMA 的句柄。
		///
		/// @note 内存 DMA 是指用来将内存中的数据拷贝到内存的 DMA.
		///
		///
		class memory_dma_handle;

		///
		/// @brief 通过 ID 打开内存 DMA.
		///
		/// @param id
		/// @return
		///
		std::shared_ptr<base::memory_dma::memory_dma_handle> open(uint32_t id);

		///
		/// @brief 初始化内存 DMA.
		///
		/// @param self
		///
		void initialize(base::memory_dma::memory_dma_handle &self);

		///
		/// @brief 初始化内存 DMA.
		///
		/// @param self
		///
		/// @param align 对齐的字节数。
		/// 	@note 对于一些特殊的外设和储存器，读写时必须满足对齐要求和最小操作粒度要求，此时如果
		/// 	要使用 DMA, 则也要将 DMA 配置为符合这些要求。
		///
		void initialize(base::memory_dma::memory_dma_handle &self, size_t align);

		///
		/// @brief 利用 DMA 将数据从 [begin, end) 内存段拷贝到 dst 指针指向的位置。
		///
		/// @param self
		/// @param begin 元数据内存段的起始位置。
		/// @param end 元数据内存段的结束位置。
		/// @param dst 要将数据拷贝到的目的地址。
		///
		void copy(base::memory_dma::memory_dma_handle &self,
				  uint8_t const *begin,
				  uint8_t const *end,
				  uint8_t *dst);

		/* #region 接口扩展 - copy */

		///
		/// @brief 利用 DMA 将数据从 src 内存段拷贝到 dst 内存段。
		///
		/// @param self
		/// @param src
		/// @param dst
		///
		IMPLEMENTED
		inline void copy(base::memory_dma::memory_dma_handle &self,
						 base::ReadOnlySpan const &src,
						 base::Span const &dst)
		{
			if (src.Size() != dst.Size())
			{
				throw std::invalid_argument{CODE_POS_STR + "要 src 和 dst 的大小不相等。"};
			}

			base::memory_dma::copy(self,
								   src.Buffer(),
								   src.Buffer() + src.Size(),
								   dst.Buffer());
		}

		///
		/// @brief 利用 DMA 将数据从 [begin, end) 内存段拷贝到 dst 内存段。
		///
		/// @param self
		/// @param begin
		/// @param end
		/// @param dst
		///
		IMPLEMENTED
		inline void copy(base::memory_dma::memory_dma_handle &self,
						 uint8_t const *begin,
						 uint8_t const *end,
						 base::Span dst)
		{
			base::ReadOnlySpan src_span{begin, end - begin};
			base::memory_dma::copy(self, src_span, dst);
		}

		///
		/// @brief 利用 DMA 将数据从 [begin, end) 内存段拷贝到 dst 指针指向的位置。
		///
		/// @param begin
		/// @param end
		/// @param dst
		///
		IMPLEMENTED
		template <typename T>
		inline void copy(base::memory_dma::memory_dma_handle &self,
						 T const *begin,
						 T const *end,
						 T *dst)
		{
			size_t count = end - begin;
			size_t size = count * sizeof(T);

			base::memory_dma::copy(self,
								   reinterpret_cast<uint8_t const *>(begin),
								   reinterpret_cast<uint8_t const *>(begin) + size,
								   reinterpret_cast<uint8_t *>(dst));
		}

		/* #endregion */

	} // namespace memory_dma
} // namespace base
