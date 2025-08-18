#include "heap.h"
#include "base/container/CircleDeque.h"
#include "base/embedded/heap/Heap4.h"
#include "base/RentedPtrFactory.h"
#include "base/task/task.h"
#include <cstdint>
#include <memory>

namespace
{
	base::CircleDeque<std::shared_ptr<base::heap::IHeap>, 10> _heaps;

} // namespace

/* #region AddHeap */

void base::heap::AddHeap(std::shared_ptr<base::heap::IHeap> const &heap)
{
	base::task::TaskSchedulerSuspendGuard g;
	if (_heaps.Count() == 0)
	{
		_heaps.PushBack(base::RentedPtrFactory::Create(&base::heap::Heap()));
	}

	_heaps.PushBack(heap);
}

void base::heap::AddHeap(uint8_t *buffer, size_t size)
{
	base::task::TaskSchedulerSuspendGuard g;
	std::shared_ptr<base::heap::Heap4> heap{new base::heap::Heap4{buffer, size}};
	base::heap::AddHeap(heap);
}

void base::heap::AddHeap(base::Span const &span)
{
	base::task::TaskSchedulerSuspendGuard g;
	AddHeap(span.Buffer(), span.Size());
}

/* #endregion */

void *base::heap::Malloc(size_t size) noexcept
{
	base::task::TaskSchedulerSuspendGuard g;
	if (_heaps.Count() == 0)
	{
		void *p = base::heap::Heap().Malloc(size);
		return p;
	}

	for (int64_t i = 0; i < _heaps.Count(); i++)
	{
		void *ptr = _heaps[i]->Malloc(size);
		if (ptr != nullptr)
		{
			return ptr;
		}
	}

	return nullptr;
}

void base::heap::Free(void *ptr) noexcept
{
	base::task::TaskSchedulerSuspendGuard g;
	if (_heaps.Count() == 0)
	{
		base::heap::Heap().Free(ptr);
		return;
	}

	for (int64_t i = 0; i < _heaps.Count(); i++)
	{
		if (ptr >= _heaps[i]->begin() && ptr < _heaps[i]->end())
		{
			_heaps[i]->Free(ptr);
			return;
		}
	}
}
