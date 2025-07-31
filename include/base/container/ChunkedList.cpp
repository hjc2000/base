#include "ChunkedList.h" // IWYU pragma: keep

#if HAS_THREAD

void base::TestChunkedList()
{
	base::ChunkedList<int> list{};
}

#endif // HAS_THREAD
