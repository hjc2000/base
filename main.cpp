#include <array>
#include <base/bit/BitConverter.h>
#include <base/container/Array.h>
#include <base/container/Dictionary.h>
#include <base/container/List.h>
#include <base/net/Mac.h>
#include <base/stream/MemoryStream.h>
#include <base/string/ToHexString.h>
#include <format>
#include <iostream>

int main()
{
    uint8_t buffer[20] = {};
    for (uint8_t i = 0; i < sizeof(buffer); i++)
    {
        buffer[i] = i;
    }

    base::Span span{buffer, sizeof(buffer)};
    base::MemoryStream stream{span};
    stream.SetLength(span.Size());

    {
        uint8_t buffer[20] = {};
        stream.Read(buffer, 0, sizeof(buffer));
        base::ToHexStringOption option;
        option.width = 2;
        for (uint8_t num : buffer)
        {
            std::cout << base::ToHexString(num) << std::endl;
        }
    }
}
