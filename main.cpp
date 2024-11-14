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
    base::IPAddress ip{
        std::endian::big,
        base::Array<uint8_t, 4>{
            192,
            168,
            1,
            1,
        },
    };

    std::cout << ip << std::endl;
}
