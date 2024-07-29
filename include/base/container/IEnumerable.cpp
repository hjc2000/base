#include "IEnumerable.h"
#include <iostream>

void base::TestIntEnumerable()
{
	{
		IntEnumerable o{};
		for (int &i : o)
		{
			std::cout << i << std::endl;
		}
	}

	{
		IntEnumerable const o{};
		for (int const &i : o)
		{
			std::cout << i << std::endl;
		}
	}
}
