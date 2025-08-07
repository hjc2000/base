#include "TestInsertingEnumerableHelper.h" // IWYU pragma: keep
#include "base/container/iterator/InsertingEnumerableHelper.h"
#include "base/container/List.h"
#include <iostream>
#include <vector>

#if HAS_THREAD

void base::test::TestInsertingEnumerableHelper()
{
	base::List<int> list{0, 1, 2, 3};
	std::vector<int> vec{6, 6, 6, 6, 6, 6};
	base::InsertingEnumerableHelper<int> helper{list, list.Count()};
	vec.insert(vec.begin() + 1, helper.begin(), helper.end());

	for (int num : vec)
	{
		std::cout << num << std::endl;
	}
}

#endif // HAS_THREAD
