#include "Stack.h"

#if HAS_THREAD
	#include <iostream>

void base::test::test_stack()
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

#endif
