#include "TestStack.h" // IWYU pragma: keep
#include "base/container/Stack.h"
#include <iostream>

void base::test::TestStack()
{
	base::Stack<int> stack;
	for (int i = 0; i < 10; i++)
	{
		stack.Push(i);
	}

	for (int i = 0; i < 10; i++)
	{
		std::cout << stack.Pop() << std::endl;
	}
}
