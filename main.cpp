#include <base/container/Dictionary.h>
#include <base/container/List.h>
#include <iostream>

int main()
{
    base::Dictionary<int, int> dic{
        {1, 2},
        {2, 2},
        {3, 2},
    };

    for (auto &pair : dic)
    {
        std::cout << pair.first << std::endl;
    }

    return 0;
}
