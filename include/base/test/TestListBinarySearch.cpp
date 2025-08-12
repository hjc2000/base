#include "TestListBinarySearch.h" // IWYU pragma: keep
#include "base/container/List.h"
#include <functional>

#if HAS_THREAD

void base::test::TestListBinarySearch()
{
	{
		base::List<int> list{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		std::cout << "二分法查找结果：" << list.AscendingOrderBinarySearch(5) << std::endl;
	}

	{
		base::List<int> list{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

		std::function<int(int const &left, int const &right)> compare = [](int const &left, int const &right) -> int
		{
			return left - right;
		};

		std::cout << "基于比较器的二分法查找结果：" << list.AscendingOrderBinarySearch(5, compare) << std::endl;
	}
}

#endif // HAS_THREAD
