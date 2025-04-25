#pragma once
#include "base/bit/bit.h"
#include <cstddef>

namespace base
{
	namespace heap
	{
		///
		/// @brief 空闲内存块链表节点。
		///
		struct MemoryBlockLinkListNode
		{
			///
			/// @brief 下一个空闲内存块。
			///
			MemoryBlockLinkListNode *_next_free_block{};

			///
			/// @brief 空闲内存块大小。
			///
			size_t _size{};
		};

		/* Check if multiplying a and b will result in overflow. */
		constexpr bool HeapMultiplyWillOverflow(size_t a, size_t b)
		{
			return ((a) > 0) && ((b) > (SIZE_MAX / (a)));
		}

		/* Check if adding a and b will result in overflow. */
		constexpr bool HeapAddWillOverflow(size_t a, size_t b)
		{
			return (a) > (SIZE_MAX - (b));
		}

		constexpr bool HeapBlockSizeIsValid(size_t _size)
		{
			return (_size & base::bit::MSB<size_t>()) == 0;
		}

		constexpr bool HeapBlockIsAllocated(MemoryBlockLinkListNode *pxBlock)
		{
			return ((pxBlock->_size) & base::bit::MSB<size_t>()) != 0;
		}

		constexpr void HeapAllocateBlock(MemoryBlockLinkListNode *pxBlock)
		{
			(pxBlock->_size) |= base::bit::MSB<size_t>();
		}

		constexpr void HeapFreeBlock(MemoryBlockLinkListNode *pxBlock)
		{
			(pxBlock->_size) &= ~base::bit::MSB<size_t>();
		}

	} // namespace heap
} // namespace base
