#include "Set.h"
#include <iostream>

#if HAS_THREAD

void base::test::test_set()
{
	base::Set<int> set{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	base::Set<int> set1{5, 6, 7, 8, 9};
	set *= set1;

	for (int i : set)
	{
		std::cout << i << ", ";
	}

	std::cout << std::endl;
	std::cout << "一共有 " << set.Count() << " 个元素" << std::endl;
}

#endif
