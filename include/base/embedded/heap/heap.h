#pragma once
#include "base/container/CircleDeque.h"
#include "base/embedded/heap/Heap4.h"
#include "base/embedded/heap/IHeap.h"
#include "base/GlobalObjectProvider.h"
#include "base/RentedPtrFactory.h"
#include "base/stream/Span.h"
#include "base/task/task.h"
#include <cstddef>
#include <cstdint>
#include <memory>

namespace base::detail::heap
{
	using HeapQueue = base::CircleDeque<std::shared_ptr<base::heap::IHeap>, 10>;

	class HeapQueueProvider
	{
	private:
		inline static base::GlobalObjectProvider<base::detail::heap::HeapQueue> _provider{};

	public:
		static base::detail::heap::HeapQueue &Instance()
		{
			return _provider.Instance();
		}
	};

	inline base::detail::heap::HeapQueue &heap_queue()
	{
		return base::detail::heap::HeapQueueProvider::Instance();
	}

} // namespace base::detail::heap

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
	inline void PushBack(std::shared_ptr<base::heap::IHeap> const &heap)
	{
		base::task::TaskSchedulerSuspendGuard g;

		if (base::detail::heap::heap_queue().Count() == 0)
		{
			base::detail::heap::heap_queue().PushBack(base::RentedPtrFactory::Create(&base::heap::Heap()));
		}

		base::detail::heap::heap_queue().PushBack(heap);
	}

	///
	/// @brief 添加一个堆到堆列表。一旦添加，堆就会投入使用，被用于动态内存分配。
	/// @param buffer
	///
	/// @param size
	///
	inline void PushBack(uint8_t *buffer, size_t size)
	{
		base::task::TaskSchedulerSuspendGuard g;
		std::shared_ptr<base::heap::Heap4> heap{new base::heap::Heap4{buffer, size}};
		base::heap::PushBack(heap);
	}

	///
	/// @brief 添加一个堆到堆列表。一旦添加，堆就会投入使用，被用于动态内存分配。
	/// @param span
	///
	inline void PushBack(base::Span const &span)
	{
		base::task::TaskSchedulerSuspendGuard g;
		PushBack(span.Buffer(), span.Size());
	}

	/* #endregion */

	/* #region PushFront */

	///
	/// @brief 添加一个堆到堆列表。一旦添加，堆就会投入使用，被用于动态内存分配。
	/// @param heap
	///
	inline void PushFront(std::shared_ptr<base::heap::IHeap> const &heap)
	{
		base::task::TaskSchedulerSuspendGuard g;

		if (base::detail::heap::heap_queue().Count() == 0)
		{
			base::detail::heap::heap_queue().PushFront(base::RentedPtrFactory::Create(&base::heap::Heap()));
		}

		base::detail::heap::heap_queue().PushFront(heap);
	}

	///
	/// @brief 添加一个堆到堆列表。一旦添加，堆就会投入使用，被用于动态内存分配。
	/// @param buffer
	///
	/// @param size
	///
	inline void PushFront(uint8_t *buffer, size_t size)
	{
		base::task::TaskSchedulerSuspendGuard g;
		std::shared_ptr<base::heap::Heap4> heap{new base::heap::Heap4{buffer, size}};
		base::heap::PushFront(heap);
	}

	///
	/// @brief 添加一个堆到堆列表。一旦添加，堆就会投入使用，被用于动态内存分配。
	/// @param span
	///
	inline void PushFront(base::Span const &span)
	{
		base::task::TaskSchedulerSuspendGuard g;
		PushFront(span.Buffer(), span.Size());
	}

	/* #endregion */

	inline void *Malloc(size_t size) noexcept
	{
		base::task::TaskSchedulerSuspendGuard g;

		if (base::detail::heap::heap_queue().Count() == 0)
		{
			void *p = base::heap::Heap().Malloc(size);
			return p;
		}

		for (int64_t i = 0; i < base::detail::heap::heap_queue().Count(); i++)
		{
			void *ptr = base::detail::heap::heap_queue()[i]->Malloc(size);
			if (ptr != nullptr)
			{
				return ptr;
			}
		}

		return nullptr;
	}

	inline void Free(void *ptr) noexcept
	{
		base::task::TaskSchedulerSuspendGuard g;

		if (base::detail::heap::heap_queue().Count() == 0)
		{
			base::heap::Heap().Free(ptr);
			return;
		}

		for (int64_t i = 0; i < base::detail::heap::heap_queue().Count(); i++)
		{
			if (ptr >= base::detail::heap::heap_queue()[i]->begin() && ptr < base::detail::heap::heap_queue()[i]->end())
			{
				base::detail::heap::heap_queue()[i]->Free(ptr);
				return;
			}
		}
	}

} // namespace base::heap
