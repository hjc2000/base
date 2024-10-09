#include <base/container/IDictionary.h>
#include <base/container/List.h>
#include <iostream>

int main()
{
    base::List<int> list{};
    for (int i = 0; i < 10; i++)
    {
        list.Add(i);
    }

    for (int i : list)
    {
        std::cout << i << std::endl;
    }

    return 0;
}
