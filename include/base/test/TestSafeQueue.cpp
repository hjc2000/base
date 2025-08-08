#include "TestSafeQueue.h" // IWYU pragma: keep
#include "base/container/SafeQueue.h"
#include "base/string/define.h"
#include <exception>
#include <iostream>

#if HAS_THREAD

void base::test::TestSafeQueue()
{
	base::SafeQueue<int> queue;
	for (int i = 0; i < 10; i++)
	{
		queue.Enqueue(i);
	}

	try
	{
		while (true)
		{
			std::cout << queue.Dequeue() << std::endl;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << CODE_POS_STR << e.what() << std::endl;
	}
}

#endif
