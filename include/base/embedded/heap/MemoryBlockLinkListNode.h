#pragma once
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

	} // namespace heap
} // namespace base
