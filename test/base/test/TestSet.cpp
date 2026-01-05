#include "TestSet.h" // IWYU pragma: keep
#include "base/container/Set.h"
#include <iostream>

void base::test::TestSet()
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
