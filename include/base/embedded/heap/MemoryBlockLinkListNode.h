#pragma once
#include "base/bit/bit.h"
#include <cstddef>
#include <cstdint>

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

		constexpr uint8_t BitCountPerByte()
		{
			return 8;
		}

		constexpr size_t SizeTypeMsbMask()
		{
			return static_cast<size_t>(base::bit::Bit((sizeof(size_t) * 8) - 1));
		}

	} // namespace heap
} // namespace base
