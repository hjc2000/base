#include "TestListBinarySearch.h" // IWYU pragma: keep
#include "base/container/List.h"

#if HAS_THREAD

void base::test::TestListBinarySearch()
{
	base::List<int> list{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::cout << "二分法查找结果：" << list.AscendingOrderBinarySearch(5) << std::endl;
}

#endif // HAS_THREAD
