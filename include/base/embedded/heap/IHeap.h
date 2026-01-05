#pragma once
#include <stddef.h>
#include <stdint.h>

namespace base
{
	namespace heap
	{
		///
		/// @brief 堆接口。
		///
		class IHeap
		{
		public:
			virtual ~IHeap() = default;

			///
			/// @brief 分配内存。
			///
			/// @param size 要分配的内存块大小。单位：字节。
			///
			/// @return
			///
			virtual void *Malloc(size_t size) noexcept = 0;

			///
			/// @brief 要释放的由 Malloc 方法分配的内存块。
			///
			/// @param p Malloc 方法返回的指针。
			///
			virtual void Free(void *p) noexcept = 0;

			///
			/// @brief 堆的起点。
			///
			/// @return
			///
			virtual uint8_t const *begin() const = 0;

			///
			/// @brief 堆的最后一个字节再 +1.
			///
			/// @return
			///
			virtual uint8_t const *end() const = 0;

			///
			/// @brief 剩余的自由空间。单位：字节。
			///
			/// @note 不一定是一整块连续的，有可能是碎片化的。
			///
			/// @return
			///
			virtual size_t RemainingFreeSize() const = 0;

			///
			/// @brief 堆的总大小。
			///
			/// @return
			///
			size_t TotalSize() const
			{
				return end() - begin();
			}

		}; // class IHeap

	} // namespace heap
} // namespace base
