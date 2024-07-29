#if HAS_THREAD
#include "VectorEnumerable.h"
#include <iostream>

void base::TestVectorEnumerable()
{
	std::vector<int> vector{1, 2, 3, 4, 5};
	base::VectorEnumerable<int> ve{vector};
	for (int &i : ve)
	{
		std::cout << i << std::endl;
	}

	base::VectorEnumerable<int> const &const_ve = ve;
	for (int const &i : const_ve)
	{
		std::cout << i << std::endl;
	}
}

#endif // HAS_THREAD
