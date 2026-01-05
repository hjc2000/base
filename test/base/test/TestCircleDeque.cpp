#include "TestCircleDeque.h" // IWYU pragma: keep
#include "base/container/CircleDeque.h"
#include "base/string/define.h"
#include <iostream>
#include <stdexcept>

void base::test::TestCircleDeque()
{
	{
		std::cout << std::endl
				  << "测试队列入队退队" << std::endl;

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
	}

	{
		std::cout << std::endl
				  << "测试入队和退队溢出异常" << std::endl;

		base::CircleDeque<int, 10> queue;

		try
		{
			for (int i = 0; i < 100; i++)
			{
				queue.PushBack(i);
			}
		}
		catch (std::exception const &e)
		{
			std::cerr << CODE_POS_STR << e.what() << std::endl;
		}
		catch (...)
		{
			std::cerr << CODE_POS_STR << "未知异常。" << std::endl;
		}

		if (queue.Count() != 10)
		{
			throw std::runtime_error{CODE_POS_STR + "测试不通过。"};
		}

		try
		{
			std::cout << "退队：";
			while (true)
			{
				int num = queue.PopFront();
				std::cout << num << ", ";
			}
		}
		catch (std::exception const &e)
		{
			std::cout << std::endl;
			std::cerr << CODE_POS_STR << e.what() << std::endl;
		}
		catch (...)
		{
			std::cout << std::endl;
			std::cerr << CODE_POS_STR << "未知异常。" << std::endl;
		}
	}

	std::cout << CODE_POS_STR << "测试通过。" << std::endl;
}
