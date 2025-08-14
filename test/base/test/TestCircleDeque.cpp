#include "TestCircleDeque.h" // IWYU pragma: keep
#include "base/container/CircleDeque.h"
#include "base/string/define.h"
#include <iostream>
#include <stdexcept>

void base::test::TestCircleDeque()
{
	base::CircleDeque<int, 10> queue;

	queue.PushBack(0);
	// 0

	queue.PushFront(1);
	// 1, 0

	queue.PushBack(1);
	// 1, 0, 1

	queue.PushBack(2);
	// 1, 0, 1, 2

	queue.PopFront();
	// 0, 1, 2

	queue.PopBack();
	// 0, 1

	if (queue.Count() != 2)
	{
		throw std::runtime_error{CODE_POS_STR + "测试不通过。"};
	}

	if (queue.Get(0) != 0)
	{
		throw std::runtime_error{CODE_POS_STR + "测试不通过。"};
	}

	if (queue.Get(1) != 1)
	{
		throw std::runtime_error{CODE_POS_STR + "测试不通过。"};
	}

	for (int num : queue)
	{
		std::cout << num << std::endl;
	}

	std::cout << CODE_POS_STR << "测试通过。" << std::endl;
}
