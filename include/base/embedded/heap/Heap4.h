#pragma once
#include "base/bit/bit.h"
#include "base/embedded/heap/IHeap.h"
#include "base/embedded/heap/MemoryBlockLinkListNode.h"
#include "base/task/task.h"
#include <cstddef>
#include <cstdint>
#include <stdlib.h>
#include <string.h>

namespace base::heap
{
	/// @brief 基于 freertos 的 heap4 的堆管理器。
	class Heap4 :
		public base::heap::IHeap
	{
	private:
		uint8_t *_buffer{};
		size_t _size{};

		/* Create a couple of list links to mark the start and end of the list. */
		base::heap::MemoryBlockLinkListNode _head_element{};
		base::heap::MemoryBlockLinkListNode *_tail_element = nullptr;

		/* Keeps track of the number of calls to allocate and free memory as well as the
		 * number of free bytes remaining, but says nothing about fragmentation. */
		size_t xFreeBytesRemaining = 0U;
		size_t xMinimumEverFreeBytesRemaining = 0U;
		size_t xNumberOfSuccessfulAllocations = 0;
		size_t xNumberOfSuccessfulFrees = 0;

		/// @brief 将被释放的内存插入链表。
		/// @note 如果发现与链表中要插入位置的前一个节点和后一个节点指向的内存是连续的，会合并这些节点。
		/// @param pxBlockToInsert
		void InsertBlockIntoFreeList(base::heap::MemoryBlockLinkListNode *pxBlockToInsert)
		{
			base::heap::MemoryBlockLinkListNode *pxIterator{};
			uint8_t *puc{};

			/* Iterate through the list until a block is found that has a higher address
			 * than the block being inserted. */
			for (pxIterator = &_head_element;
				 pxIterator->_next_free_block < pxBlockToInsert;
				 pxIterator = pxIterator->_next_free_block)
			{
				/* Nothing to do here, just iterate to the right position. */
			}

			/* Do the block being inserted, and the block it is being inserted after
			 * make a contiguous block of memory? */
			puc = (uint8_t *)pxIterator;

			if ((puc + pxIterator->_size) == (uint8_t *)pxBlockToInsert)
			{
				pxIterator->_size += pxBlockToInsert->_size;
				pxBlockToInsert = pxIterator;
			}

			/* Do the block being inserted, and the block it is being inserted before
			 * make a contiguous block of memory? */
			puc = (uint8_t *)pxBlockToInsert;

			if ((puc + pxBlockToInsert->_size) == (uint8_t *)pxIterator->_next_free_block)
			{
				if (pxIterator->_next_free_block != _tail_element)
				{
					/* Form one big block from the two blocks. */
					pxBlockToInsert->_size += pxIterator->_next_free_block->_size;
					pxBlockToInsert->_next_free_block = pxIterator->_next_free_block->_next_free_block;
				}
				else
				{
					pxBlockToInsert->_next_free_block = _tail_element;
				}
			}
			else
			{
				pxBlockToInsert->_next_free_block = pxIterator->_next_free_block;
			}

			/* If the block being inserted plugged a gab, so was merged with the block
			 * before and the block after, then it's _next_free_block pointer will have
			 * already been set, and should not be set here as that would make it point
			 * to itself. */
			if (pxIterator != pxBlockToInsert)
			{
				pxIterator->_next_free_block = pxBlockToInsert;
			}
		}

	public:
		/// @brief 构造一个基于 freertos 的 heap4 的堆管理器。
		/// @param buffer 要被作为堆的缓冲区。
		/// @param size 缓冲区大小。
		Heap4(uint8_t *buffer, size_t size)
		{
			/* Ensure the heap starts on a correctly aligned boundary. */
			_buffer = base::bit::AlignUp(buffer, 8);
			_size = size - static_cast<size_t>(_buffer - buffer);

			/* _head_element is used to hold a pointer to the first item in the list of free
			 * blocks.  The void cast is used to prevent compiler warnings. */
			_head_element._next_free_block = reinterpret_cast<base::heap::MemoryBlockLinkListNode *>(_buffer);
			_head_element._size = 0;

			/* _tail_element is used to mark the end of the list of free blocks and is inserted
			 * at the end of the heap space. */
			uint8_t *tail_addr = base::bit::AlignDown(_buffer + _size - base::bit::GetAlignedSize<base::heap::MemoryBlockLinkListNode>());
			_tail_element = reinterpret_cast<base::heap::MemoryBlockLinkListNode *>(tail_addr);
			_tail_element->_next_free_block = nullptr;
			_tail_element->_size = 0;

			/* To start with there is a single free block that is sized to take up the
			 * entire heap space, minus the space taken by _tail_element. */
			base::heap::MemoryBlockLinkListNode *pxFirstFreeBlock = reinterpret_cast<base::heap::MemoryBlockLinkListNode *>(_buffer);
			pxFirstFreeBlock->_next_free_block = _tail_element;
			pxFirstFreeBlock->_size = static_cast<size_t>(tail_addr - _buffer);

			/* Only one block exists - and it covers the entire usable heap space. */
			xMinimumEverFreeBytesRemaining = pxFirstFreeBlock->_size;
			xFreeBytesRemaining = pxFirstFreeBlock->_size;
		}

		/// @brief 分配内存。
		/// @param size 要分配的内存块大小。单位：字节。
		/// @return
		virtual void *Malloc(size_t xWantedSize) noexcept override
		{
			base::heap::MemoryBlockLinkListNode *pxBlock;
			base::heap::MemoryBlockLinkListNode *pxPreviousBlock;
			base::heap::MemoryBlockLinkListNode *pxNewBlockLink;
			void *pvReturn = nullptr;

			{
				base::task::TaskSchedulerSuspendGuard g{};

				/* If this is the first call to malloc then the heap will require
				 * initialisation to setup the list of free blocks. */
				if (_tail_element == nullptr)
				{
					// 已被构造函数取代。
					//  prvHeapInit();
				}

				if (xWantedSize > 0)
				{
					size_t required_size = base::bit::AlignUp(xWantedSize + base::bit::GetAlignedSize<base::heap::MemoryBlockLinkListNode>());
					if (xWantedSize > required_size)
					{
						// 加上 base::bit::GetAlignedSize<base::heap::MemoryBlockLinkListNode>() 的大小
						// 并向上对齐后变得比 xWantedSize 小，说明溢出了。
						xWantedSize = 0;
					}
					else
					{
						xWantedSize = required_size;
					}
				}

				/* Check the block size we are trying to allocate is not so large that the
				 * top bit is set.  The top bit of the block size member of the MemoryBlockLinkListNode
				 * structure is used to determine who owns the block - the application or
				 * the kernel, so it must be free. */
				if (base::heap::HeapBlockSizeIsValid(xWantedSize))
				{
					if ((xWantedSize > 0) && (xWantedSize <= xFreeBytesRemaining))
					{
						/* Traverse the list from the start (lowest address) block until
						 * one of adequate size is found. */
						pxPreviousBlock = &_head_element;
						pxBlock = _head_element._next_free_block;

						while ((pxBlock->_size < xWantedSize) && (pxBlock->_next_free_block != nullptr))
						{
							pxPreviousBlock = pxBlock;
							pxBlock = pxBlock->_next_free_block;
						}

						/* If the end marker was reached then a block of adequate size
						 * was not found. */
						if (pxBlock != _tail_element)
						{
							/* Return the memory space pointed to - jumping over the
							 * MemoryBlockLinkListNode structure at its start. */
							pvReturn = (void *)(((uint8_t *)pxPreviousBlock->_next_free_block) + base::bit::GetAlignedSize<base::heap::MemoryBlockLinkListNode>());

							/* This block is being returned for use so must be taken out
							 * of the list of free blocks. */
							pxPreviousBlock->_next_free_block = pxBlock->_next_free_block;

							/* If the block is larger than required it can be split into
							 * two. */
							if ((pxBlock->_size - xWantedSize) > base::heap::MinimumBlockSize())
							{
								/* This block is to be split into two.  Create a new
								 * block following the number of bytes requested. The void
								 * cast is used to prevent byte alignment warnings from the
								 * compiler. */
								pxNewBlockLink = (base::heap::MemoryBlockLinkListNode *)(((uint8_t *)pxBlock) + xWantedSize);

								/* Calculate the sizes of two blocks split from the
								 * single block. */
								pxNewBlockLink->_size = pxBlock->_size - xWantedSize;
								pxBlock->_size = xWantedSize;

								/* Insert the new block into the list of free blocks. */
								InsertBlockIntoFreeList(pxNewBlockLink);
							}

							xFreeBytesRemaining -= pxBlock->_size;

							if (xFreeBytesRemaining < xMinimumEverFreeBytesRemaining)
							{
								xMinimumEverFreeBytesRemaining = xFreeBytesRemaining;
							}

							/* The block is being returned - it is allocated and owned
							 * by the application and has no "next" block. */
							HeapAllocateBlock(pxBlock);
							pxBlock->_next_free_block = nullptr;
							xNumberOfSuccessfulAllocations++;
						}
					}
				}
			}

			return pvReturn;
		}

		/// @brief 要释放的由 Malloc 方法分配的内存块。
		/// @param p Malloc 方法返回的指针。
		virtual void Free(void *pv) noexcept override
		{
			uint8_t *puc = (uint8_t *)pv;
			base::heap::MemoryBlockLinkListNode *pxLink;

			if (pv != nullptr)
			{
				/* The memory being freed will have an MemoryBlockLinkListNode structure immediately
				 * before it. */
				puc -= base::bit::GetAlignedSize<base::heap::MemoryBlockLinkListNode>();

				/* This casting is to keep the compiler from issuing warnings. */
				pxLink = (base::heap::MemoryBlockLinkListNode *)puc;

				if (HeapBlockIsAllocated(pxLink))
				{
					if (pxLink->_next_free_block == nullptr)
					{
						/* The block is being returned to the heap - it is no longer
						 * allocated. */
						HeapFreeBlock(pxLink);

						{
							base::task::TaskSchedulerSuspendGuard g{};

							/* Add this block to the list of free blocks. */
							xFreeBytesRemaining += pxLink->_size;
							InsertBlockIntoFreeList(((base::heap::MemoryBlockLinkListNode *)pxLink));
							xNumberOfSuccessfulFrees++;
						}
					}
				}
			}
		}

		/// @brief 堆的起点。
		/// @return
		virtual uint8_t const *begin() const override
		{
			return _buffer;
		}

		/// @brief 堆的最后一个字节再 +1.
		/// @return
		virtual uint8_t const *end() const override
		{
			return _buffer + _size;
		}

		/// @brief 剩余的自由空间。单位：字节。
		/// @note 不一定是一整块连续的，有可能是碎片化的。
		/// @return
		virtual size_t RemainingFreeSize() const override
		{
			return xFreeBytesRemaining;
		}
	};

} // namespace base::heap
