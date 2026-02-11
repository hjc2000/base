#include "heap.h" // IWYU pragma: keep

#if !HAS_THREAD

	#include "base/container/CircleDeque.h"
	#include "base/embedded/heap/Heap4.h"
	#include "base/RentedPtrFactory.h"
	#include "base/SingletonProvider.h"
	#include "base/task/task.h"
	#include <cstdint>
	#include <memory>

namespace
{
	using Queue = base::CircleDeque<std::shared_ptr<base::heap::IHeap>, 10>;

	base::SingletonProvider<Queue> _queue_provider{};

} // namespace

/* #region PushBack */

void base::heap::PushBack(std::shared_ptr<base::heap::IHeap> const &heap)
{
	base::task::TaskSchedulerSuspendGuard g;

	if (_queue_provider.Instance().Count() == 0)
	{
		_queue_provider.Instance().PushBack(base::RentedPtrFactory::Create(&base::heap::Heap()));
	}

	_queue_provider.Instance().PushBack(heap);
}

void base::heap::PushBack(uint8_t *buffer, size_t size)
{
	base::task::TaskSchedulerSuspendGuard g;
	std::shared_ptr<base::heap::Heap4> heap{new base::heap::Heap4{buffer, size}};
	base::heap::PushBack(heap);
}

void base::heap::PushBack(base::Span const &span)
{
	base::task::TaskSchedulerSuspendGuard g;
	PushBack(span.Buffer(), span.Size());
}

/* #endregion */

/* #region PushFront */

void base::heap::PushFront(std::shared_ptr<base::heap::IHeap> const &heap)
{
	base::task::TaskSchedulerSuspendGuard g;

	if (_queue_provider.Instance().Count() == 0)
	{
		_queue_provider.Instance().PushFront(base::RentedPtrFactory::Create(&base::heap::Heap()));
	}

	_queue_provider.Instance().PushFront(heap);
}

void base::heap::PushFront(uint8_t *buffer, size_t size)
{
	base::task::TaskSchedulerSuspendGuard g;
	std::shared_ptr<base::heap::Heap4> heap{new base::heap::Heap4{buffer, size}};
	base::heap::PushFront(heap);
}

void base::heap::PushFront(base::Span const &span)
{
	base::task::TaskSchedulerSuspendGuard g;
	PushFront(span.Buffer(), span.Size());
}

/* #endregion */

void *base::heap::Malloc(size_t size) noexcept
{
	base::task::TaskSchedulerSuspendGuard g;

	if (_queue_provider.Instance().Count() == 0)
	{
		void *p = base::heap::Heap().Malloc(size);
		return p;
	}

	for (int64_t i = 0; i < _queue_provider.Instance().Count(); i++)
	{
		void *ptr = _queue_provider.Instance()[i]->Malloc(size);
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

	if (_queue_provider.Instance().Count() == 0)
	{
		base::heap::Heap().Free(ptr);
		return;
	}

	for (int64_t i = 0; i < _queue_provider.Instance().Count(); i++)
	{
		if (ptr >= _queue_provider.Instance()[i]->begin() && ptr < _queue_provider.Instance()[i]->end())
		{
			_queue_provider.Instance()[i]->Free(ptr);
			return;
		}
	}
}

#endif // HAS_THREAD
