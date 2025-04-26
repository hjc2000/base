#include "base/embedded/heap/heap.h"

///
/// @brief 实现 freertos 的函数。
///
///
extern "C"
{
	void *pvPortMalloc(size_t xWantedSize)
	{
		return base::heap::Malloc(xWantedSize);
	}

	void vPortFree(void *pv)
	{
		base::heap::Free(pv);
	}
}
