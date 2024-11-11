#include <array>
#include <base/bit/BitConverter.h>
#include <base/container/Array.h>
#include <base/container/Dictionary.h>
#include <base/container/List.h>
#include <base/net/Mac.h>
#include <base/string/ToHexString.h>
#include <format>
#include <iostream>

int main()
{
    base::Mac mac{std::endian::big, {0x01, 0x0e, 0xcf, 0x00, 0x04, 0x00}};
    std::cout << mac << std::endl;
}
