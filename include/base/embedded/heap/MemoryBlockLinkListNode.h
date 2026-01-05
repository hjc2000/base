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

		///
		/// @brief 允许的内存块的最小大小。
		///
		/// @note 如果内存块大小小于此值的话，链表节点本身占用的内存都比指向的内存块大了，
		/// 那这块内存就不值得用一个链表节点去指向它。
		///
		/// @return
		///
		constexpr size_t MinimumBlockSize()
		{
			size_t ret = base::bit::GetAlignedSize<base::heap::MemoryBlockLinkListNode>() * 2;
			return ret;
		}

	} // namespace heap
} // namespace base
