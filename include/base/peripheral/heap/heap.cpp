#include "heap.h"
#include "base/RentedPtrFactory.h"
#include "base/task/task.h"
#include <vector>

namespace
{
	// 这里一定要使用普通指针，不能直接构造 std::vector 对象，然后指望在 Malloc 和 Free
	// 函数中检查 std::vector 的 size. 因为 std::vector 的构造本身需要动态内存分配，
	// 于是就会造成 std::vector 构造到一半， 调用了 Malloc 函数，而 Malloc 函数又去访
	// 问未构造完成的 std::vector 的 size 方法。
	std::vector<std::shared_ptr<base::heap::IHeap>> *_heap_vector = nullptr;

} // namespace

/* #region AddHeap */

void base::heap::AddHeap(std::shared_ptr<base::heap::IHeap> const &heap)
{
	base::task::TaskSchedulerSuspendGuard g;
	if (_heap_vector == nullptr)
	{
		std::vector<std::shared_ptr<base::heap::IHeap>> *vec = new std::vector<std::shared_ptr<base::heap::IHeap>>{};
		vec->push_back(heap);
		vec->push_back(base::RentedPtrFactory::Create(&base::heap::Heap()));
		_heap_vector = vec;
		return;
	}

	_heap_vector->push_back(heap);
}

void base::heap::AddHeap(uint8_t *buffer, size_t size)
{
	base::task::TaskSchedulerSuspendGuard g;
	base::heap::AddHeap(base::heap::CreateHeap(buffer, size));
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
	if (_heap_vector == nullptr)
	{
		void *p = base::heap::Heap().Malloc(size);
		return p;
	}

	for (std::shared_ptr<base::heap::IHeap> &heap : *_heap_vector)
	{
		void *ptr = heap->Malloc(size);
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
	if (_heap_vector == nullptr)
	{
		base::heap::Heap().Free(ptr);
		return;
	}

	for (std::shared_ptr<base::heap::IHeap> &heap : *_heap_vector)
	{
		if (ptr >= heap->begin() && ptr < heap->end())
		{
			heap->Free(ptr);
			return;
		}
	}
}
