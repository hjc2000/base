#include "Set.h"
#include <iostream>

#if HAS_THREAD

void base::test::test_set()
{
	base::Set<int> set;
	for (int i = 0; i < 10; i++)
	{
		set.Add(i);
		set.Add(i);
	}

	for (int i : set)
	{
		std::cout << i << std::endl;
	}

	std::cout << "一共有 " << set.Count() << " 个元素" << std::endl;
}

#endif
