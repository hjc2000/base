#include <base/container/IDictionary.h>
#include <base/container/List.h>
#include <iostream>

int main()
{
    std::map<int, int> m{};
    for (auto &pair : m)
    {
        std::cout << pair.first << std::endl;
    }

    return 0;
}
