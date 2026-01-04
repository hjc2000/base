#pragma once
#include "base/embedded/heap/IHeap.h"
#include "base/stream/Span.h"
#include <cstddef>
#include <memory>

namespace base::heap
{
	///
	/// @brief 获取主堆。
	///
	/// @return
	///
	base::heap::IHeap &Heap();

	/* #region PushBack */

	///
	/// @brief 添加一个堆到堆列表。一旦添加，堆就会投入使用，被用于动态内存分配。
	/// @param heap
	///
	void PushBack(std::shared_ptr<base::heap::IHeap> const &heap);

	///
	/// @brief 添加一个堆到堆列表。一旦添加，堆就会投入使用，被用于动态内存分配。
	/// @param buffer
	///
	/// @param size
	///
	void PushBack(uint8_t *buffer, size_t size);

	///
	/// @brief 添加一个堆到堆列表。一旦添加，堆就会投入使用，被用于动态内存分配。
	/// @param span
	///
	void PushBack(base::Span const &span);

	/* #endregion */

	/* #region PushFront */

	///
	/// @brief 添加一个堆到堆列表。一旦添加，堆就会投入使用，被用于动态内存分配。
	/// @param heap
	///
	void PushFront(std::shared_ptr<base::heap::IHeap> const &heap);

	///
	/// @brief 添加一个堆到堆列表。一旦添加，堆就会投入使用，被用于动态内存分配。
	/// @param buffer
	///
	/// @param size
	///
	void PushFront(uint8_t *buffer, size_t size);

	///
	/// @brief 添加一个堆到堆列表。一旦添加，堆就会投入使用，被用于动态内存分配。
	/// @param span
	///
	void PushFront(base::Span const &span);

	/* #endregion */

	void *Malloc(size_t size) noexcept;

	void Free(void *ptr) noexcept;

} // namespace base::heap
