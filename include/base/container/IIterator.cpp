#include "IIterator.h"
#include <iostream>

void base::TestIntEnumerable()
{
	IntEnumerable o{};
	for (int i : o)
	{
		std::cout << i << std::endl;
	}
}
