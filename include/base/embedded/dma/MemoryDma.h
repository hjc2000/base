#pragma once
#include "memory_dma_handle.h"
#include <cstddef>
#include <cstdint>
#include <memory>

namespace base
{
	namespace memory_dma
	{
		class MemoryDma
		{
		private:
			std::shared_ptr<base::memory_dma::memory_dma_handle> _handle;

		public:
			MemoryDma(uint32_t id)
			{
				_handle = base::memory_dma::open(id);
			}

			///
			/// @brief 初始化内存 DMA.
			///
			///
			void Initialize()
			{
				base::memory_dma::initialize(*_handle);
			}

			///
			/// @brief 初始化内存 DMA.
			///
			/// @param align
			///
			void Initialize(size_t align)
			{
				base::memory_dma::initialize(*_handle, align);
			}

			/* #region Copy */

			///
			/// @brief 利用 DMA 将数据从 [begin, end) 内存段拷贝到 dst 指针指向的位置。
			///
			/// @param begin 元数据内存段的起始位置。
			/// @param end 元数据内存段的结束位置。
			/// @param dst 要将数据拷贝到的目的地址。
			///
			void Copy(uint8_t const *begin,
					  uint8_t const *end,
					  uint8_t *dst)
			{
				base::memory_dma::copy(*_handle, begin, end, dst);
			}

			///
			/// @brief 利用 DMA 将数据从 src 内存段拷贝到 dst 内存段。
			///
			/// @param src
			/// @param dst
			///
			void Copy(base::ReadOnlySpan const &src,
					  base::Span const &dst)
			{
				base::memory_dma::copy(*_handle, src, dst);
			}

			///
			/// @brief 利用 DMA 将数据从 [begin, end) 内存段拷贝到 dst 内存段。
			///
			/// @param begin
			/// @param end
			/// @param dst
			///
			void Copy(uint8_t const *begin,
					  uint8_t const *end,
					  base::Span dst)
			{
				base::memory_dma::copy(*_handle, begin, end, dst);
			}

			///
			/// @brief 利用 DMA 将数据从 [begin, end) 内存段拷贝到 dst 指针指向的位置。
			///
			/// @param begin
			/// @param end
			/// @param dst
			/// @return
			///
			template <typename T>
			void Copy(T const *begin, T const *end, T *dst)
			{
				base::memory_dma::copy<T>(*_handle, begin, end, dst);
			}

			/* #endregion */
		};

	} // namespace memory_dma
} // namespace base
