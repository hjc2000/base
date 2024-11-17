#include <array>
#include <base/bit/BitConverter.h>
#include <base/container/Array.h>
#include <base/container/Dictionary.h>
#include <base/container/List.h>
#include <base/net/IPAddress.h>
#include <base/net/Mac.h>
#include <base/stream/MemoryStream.h>
#include <base/string/StringHelper.h>
#include <base/string/ToHexString.h>
#include <format>
#include <iostream>

int main()
{
    uint8_t buffer[] = {1, 2, 3, 4, 5, 6};
    base::Span span{buffer, sizeof(buffer)};
    for (uint8_t num : buffer)
    {
        std::cout << static_cast<int>(num) << std::endl;
    }

    span.FillWithZero();
    for (uint8_t num : buffer)
    {
        std::cout << static_cast<int>(num) << std::endl;
    }
}
