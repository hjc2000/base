#include "TestInsertingEnumerableHelper.h" // IWYU pragma: keep
#include "base/container/iterator/InsertingEnumerableHelper.h"
#include "base/container/List.h"
#include <deque>
#include <iostream>
#include <vector>

#if HAS_THREAD

void base::test::TestInsertingEnumerableHelper()
{
	{
		base::List<int> list{0, 1, 2, 3};
		std::vector<int> vector{6, 6, 6, 6, 6, 6};
		base::InsertingEnumerableHelper<int> helper{list, list.Count()};
		vector.insert(vector.begin() + 1, helper.begin(), helper.end());

		for (int num : vector)
		{
			std::cout << num << std::endl;
		}
	}

	{
		// base::List<int> list{0, 1, 2, 3};
		// std::deque<int> deque{6, 6, 6, 6, 6, 6};
		// base::InsertingEnumerableHelper<int> helper{list, list.Count()};
		// deque.insert(deque.begin() + 1, helper.begin(), helper.end());

		// for (int num : deque)
		// {
		// 	std::cout << num << std::endl;
		// }
	}
}

#endif // HAS_THREAD
