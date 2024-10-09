#include <array>
#include <base/container/Array.h>
#include <base/container/Dictionary.h>
#include <base/container/List.h>
#include <format>
#include <iostream>

int main()
{
    int buffer[6] = {1, 2, 3, 4, 5, 6};
    base::Array<int, 10> arr{};
    arr.CopyFrom(buffer, 0, sizeof(buffer) / sizeof(int));
    for (int i : arr)
    {
        std::cout << i << std::endl;
    }

    return 0;
}
