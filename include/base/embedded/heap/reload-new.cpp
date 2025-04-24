#include "base/embedded/heap/heap.h"
#include <cstddef>

#if !HAS_THREAD

void *operator new(size_t size)
{
	void *ret = base::heap::Malloc(size);
	if (ret == nullptr)
	{
		throw std::bad_alloc{};
	}

	return ret;
}

void *operator new[](size_t size)
{
	void *ret = base::heap::Malloc(size);
	if (ret == nullptr)
	{
		throw std::bad_alloc{};
	}

	return ret;
}

void *operator new(size_t size, std::nothrow_t const &) noexcept
{
	void *ret = base::heap::Malloc(size);
	return ret;
}

void *operator new[](size_t size, std::nothrow_t const &) noexcept
{
	void *ret = base::heap::Malloc(size);
	return ret;
}

void operator delete(void *ptr) noexcept
{
	if (ptr == nullptr)
	{
		return;
	}

	base::heap::Free(ptr);
}

void operator delete[](void *ptr) noexcept
{
	if (ptr == nullptr)
	{
		return;
	}

	base::heap::Free(ptr);
}

void operator delete(void *ptr, std::nothrow_t const &) noexcept
{
	if (ptr == nullptr)
	{
		return;
	}

	base::heap::Free(ptr);
}

void operator delete[](void *ptr, std::nothrow_t const &) noexcept
{
	if (ptr == nullptr)
	{
		return;
	}

	base::heap::Free(ptr);
}

void operator delete(void *ptr, size_t size) noexcept
{
	if (ptr == nullptr)
	{
		return;
	}

	base::heap::Free(ptr);
}

void operator delete[](void *ptr, size_t size) noexcept
{
	if (ptr == nullptr)
	{
		return;
	}

	base::heap::Free(ptr);
}

#endif // !HAS_THREAD
