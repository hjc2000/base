#include "TestIRandomAccessEnumerable.h" // IWYU pragma: keep
#include "base/container/ChunkedList.h"
#include "base/container/List.h"
#include <deque>
#include <iostream>
#include <vector>

#if HAS_THREAD

void base::test::TestIRandomAccessEnumerable()
{
	{
		std::cout << std::endl
				  << "测试 std::vector" << std::endl;

		base::List<int> list{0, 1, 2, 3};
		std::vector<int> vector{6, 6, 6, 6, 6, 6};
		vector.insert(vector.begin() + 1, list.begin(), list.end());

		for (int num : vector)
		{
			std::cout << num << ", ";
		}

		std::cout << std::endl;
	}

	{
		std::cout << std::endl
				  << "测试 std::deque" << std::endl;

		base::ChunkedList<int> list{0, 1, 2, 3};
		std::deque<int> deque{6, 6, 6, 6, 6, 6};
		deque.insert(deque.begin() + 1, list.begin(), list.end());

		for (int num : deque)
		{
			std::cout << num << ", ";
		}

		std::cout << std::endl;
	}
}

#endif // HAS_THREAD
