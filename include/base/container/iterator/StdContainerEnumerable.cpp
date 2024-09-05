#include "StdContainerEnumerable.h"

#if HAS_THREAD
#include <iostream>
#include <vector>

void base::TestStdContainerEnumerable()
{
    std::shared_ptr<std::vector<int>> vector{new std::vector<int>{1, 2, 3, 4, 5}};
    base::StdContainerEnumerable<int, std::vector<int>> ve{vector};
    for (int &i : ve)
    {
        std::cout << i << std::endl;
    }

    base::StdContainerEnumerable<int, std::vector<int>> const &const_ve = ve;
    for (int const &i : const_ve)
    {
        std::cout << i << std::endl;
    }
}

#endif // HAS_THREAD
