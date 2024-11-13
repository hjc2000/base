#include <array>
#include <base/bit/BitConverter.h>
#include <base/container/Array.h>
#include <base/container/Dictionary.h>
#include <base/container/List.h>
#include <base/net/Mac.h>
#include <base/stream/MemoryStream.h>
#include <base/string/StringHelper.h>
#include <base/string/ToHexString.h>
#include <format>
#include <iostream>

int main()
{
    std::string str = "123,456,789";
    std::vector<std::string> str_vector = base::Split(str, ',');
    for (std::string &str : str_vector)
    {
        std::cout << str << std::endl;
    }
}
